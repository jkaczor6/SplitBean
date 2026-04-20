#include "SequenceDoor.h"
#include "DoorButton.h"
#include "Net/UnrealNetwork.h"
#include "SequenceDisplay.h"
#include "Kismet/GameplayStatics.h"

ASequenceDoor::ASequenceDoor()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	SetRootComponent(DoorMesh);
}

void ASequenceDoor::BeginPlay()
{
	Super::BeginPlay();
	
	if (!HasAuthority()) return;
	
	for (int32 i = 0; i < Buttons.Num(); i++)
	{
		CorrectSequence.Add(i);
	}
	
	ShuffleSequence();
	
	for (ADoorButton* Button: Buttons)
	{
		if (Button)
		{
			Button->OnButtonActivated.AddDynamic(this, &ASequenceDoor::OnButtonPressed);
		}
	}
}

void ASequenceDoor::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASequenceDoor, CorrectSequence);
}

void ASequenceDoor::MulticastPlaySound_Implementation(USoundBase* SFX)
{
	UGameplayStatics::PlaySound2D(GetWorld(), SFX);
}

void ASequenceDoor::OnButtonPressed(int32 Index)
{
	if (!HasAuthority()) return;
	if (PlayerSequence.Num() >= CorrectSequence.Num()) return;
	
	PlayerSequence.Add(Index);
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, 
		FString::Printf(TEXT("Pressed: %d, Expected: %d"), Index, CorrectSequence[PlayerSequence.Num() - 1]));

	CheckSequence();
}

void ASequenceDoor::ShuffleSequence()
{
	for (int32 i = CorrectSequence.Num() - 1; i > 0; i--)
	{
		int32 j = FMath::RandRange(0, i);
		CorrectSequence.Swap(i,j);
	}
	
	if (Display) Display->UpdateDisplay();
}

void ASequenceDoor::CheckSequence()
{
	int32 Step = PlayerSequence.Num() - 1;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange,
		FString::Printf(TEXT("Step %d: Player=%d Correct=%d"),
			Step, PlayerSequence[Step], CorrectSequence[Step]));
	
	if (PlayerSequence[Step] != CorrectSequence[Step])
	{
		ShuffleSequence();
		ResetPlayerSequence();
		MulticastOnFail();
		return;
	}
	
	if (PlayerSequence.Num() == CorrectSequence.Num())
	{
		MulticastOnSuccess();
	}
}

void ASequenceDoor::ResetPlayerSequence()
{
	PlayerSequence.Empty();
}

void ASequenceDoor::MulticastOnSuccess_Implementation()
{
	MulticastPlaySound(SuccessSFX);
	Destroy();
}

void ASequenceDoor::MulticastOnFail_Implementation()
{
	MulticastPlaySound(FailSFX);
}

