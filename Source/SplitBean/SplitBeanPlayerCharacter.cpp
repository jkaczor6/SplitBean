#include "SplitBeanPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "PauseMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "DoorButton.h"

ASplitBeanPlayerCharacter::ASplitBeanPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetMesh());
}

void ASplitBeanPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* APC = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(APC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC, 0);
		}
	}
	
	PauseMenuWidget = CreateWidget<UPauseMenuWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0 ), PauseMenuWidgetClass);
	if (PauseMenuWidget)
	{
		PauseMenuWidget->AddToViewport();
		PauseMenuWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ASplitBeanPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ASplitBeanPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Movement
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASplitBeanPlayerCharacter::MoveInput);
		
		// Looking
		EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASplitBeanPlayerCharacter::LookInput);
		
		// Jumping
		EIC->BindAction(JumpAction, ETriggerEvent::Started, this, &ASplitBeanPlayerCharacter::JumpInputStart);
		EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &ASplitBeanPlayerCharacter::JumpInputEnd);
		
		// Using
		EIC->BindAction(UseAction, ETriggerEvent::Started, this, &ASplitBeanPlayerCharacter::UseInput);
		
		// Pausing
		EIC->BindAction(PauseAction, ETriggerEvent::Started, this, &ASplitBeanPlayerCharacter::PauseInput);
	}

}

void ASplitBeanPlayerCharacter::MoveInput(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();
	
	AddMovementInput(GetActorRightVector(), MoveVector.X);
	AddMovementInput(GetActorForwardVector(), MoveVector.Y);
}

void ASplitBeanPlayerCharacter::LookInput(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	AddControllerYawInput(-LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void ASplitBeanPlayerCharacter::JumpInputStart(const FInputActionValue& Value)
{
	Jump();
}

void ASplitBeanPlayerCharacter::JumpInputEnd(const FInputActionValue& Value)
{
	StopJumping();
}

void ASplitBeanPlayerCharacter::UseInput(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Interact")));
	
	FVector Start = Camera->GetComponentLocation();
	FVector End = Start + (Camera->GetForwardVector() * MaxInteractionDistance);

	FCollisionShape InteractionSphere = FCollisionShape::MakeSphere(5.0f);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	
	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel1, InteractionSphere, Params);
	if (HasHit)
	{
		AActor* HitActor = HitResult.GetActor();
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Interacted with actor %s"), *HitActor->GetActorNameOrLabel()));
		if (ADoorButton* Button = Cast<ADoorButton>(HitActor))
		{
			Button->Activate();
		}
	}
}

void ASplitBeanPlayerCharacter::PauseInput(const FInputActionValue& Value)
{
	if (!PauseMenuWidget) return;
	if (PauseMenuWidget->GetVisibility() == ESlateVisibility::Visible) return;
	
	PauseMenuWidget->SetVisibility(ESlateVisibility::Visible);
	
	APlayerController* APC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	if (!APC) return;
	
	APC->SetShowMouseCursor(true);
	
	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(PauseMenuWidget->TakeWidget());
	APC->SetInputMode(Mode);
}

void ASplitBeanPlayerCharacter::SwitchTeams(int32 NewTeamIndex)
{
	TeamIndex = NewTeamIndex;
	switch (TeamIndex)
	{
	default:
		GetMesh()->SetMaterial(0, DefaultMaterial);
		break;
	case 1:
		GetMesh()->SetMaterial(0, RedMaterial);
		break;
	case 2:
		GetMesh()->SetMaterial(0, BlueMaterial);
		break;
		
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Joined Team %d"), TeamIndex));
}

