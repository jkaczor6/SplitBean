#include "SplitBeanPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"

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
}

