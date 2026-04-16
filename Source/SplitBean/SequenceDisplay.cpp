#include "SequenceDisplay.h"
#include "Components/PointLightComponent.h"
#include "Components/TextRenderComponent.h"
#include "SequenceDoor.h"

ASequenceDisplay::ASequenceDisplay()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	for (int32 i = 0; i < 5; i++)
	{
		UPointLightComponent* Light = CreateDefaultSubobject<UPointLightComponent>(*FString::Printf(TEXT("Light_%d"), i));
		Light->SetupAttachment(RootComponent);
		Light->SetRelativeLocation(FVector(0.0f, i * 100.0f, 0.0f));
		Light->SetIntensity(1000.0f);
		Light->CastShadows = 0;
		Lights.Add(Light);
		
		UTextRenderComponent* Text = CreateDefaultSubobject<UTextRenderComponent>(*FString::Printf(TEXT("Text_%d"), i));
		Text->SetupAttachment(RootComponent);
		Text->SetRelativeLocation(FVector(0.0f, i * 100.0f, 0.0f));
		Text->SetWorldSize(60.0f);
		Text->SetHorizontalAlignment(EHTA_Center);
		Text->SetTextRenderColor(FColor::Black);
		Numbers.Add(Text);
	}
}

void ASequenceDisplay::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle InitTimer;
	GetWorldTimerManager().SetTimer(InitTimer, this, &ASequenceDisplay::UpdateDisplay, 0.2f, false);
}

void ASequenceDisplay::UpdateDisplay()
{
	if (!SequenceDoor) return;
	if (SequenceDoor->CorrectSequence.Num() == 0) return;
	
	for (int32 i = 0; i < 5; i++)
	{
		int32 Position = SequenceDoor->CorrectSequence.Find(i);
		
		if (ButtonColors.IsValidIndex(i))
		{
			Lights[i]->SetLightColor(ButtonColors[i]);
		}
		
		Numbers[i]->SetText(FText::FromString(FString::FromInt(Position + 1)));
	}
}

