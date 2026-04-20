#include "MirrorCamera.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"

AMirrorCamera::AMirrorCamera()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("CaptureComponent"));
	SetRootComponent(CaptureComponent);

	CaptureComponent->ProjectionType = ECameraProjectionMode::Orthographic;
	CaptureComponent->OrthoWidth = 3000.f;
	CaptureComponent->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;
	CaptureComponent->bCaptureEveryFrame = true;
}

void AMirrorCamera::BeginPlay()
{
	Super::BeginPlay();
	
	if (RenderTarget)
	{
		CaptureComponent->TextureTarget = RenderTarget;
	}
}