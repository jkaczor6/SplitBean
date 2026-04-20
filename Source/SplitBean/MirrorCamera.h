#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MirrorCamera.generated.h"

class USceneCaptureComponent2D;
class UTextureRenderTarget2D;

UCLASS()
class SPLITBEAN_API AMirrorCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	AMirrorCamera();
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USceneCaptureComponent2D* CaptureComponent;
	UPROPERTY(EditAnywhere)
	UTextureRenderTarget2D* RenderTarget;
};
