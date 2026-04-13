#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class SPLITBEAN_API AMovingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovingActor();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	bool GetShouldMove();
	void SetShouldMove(bool NewShouldMove);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere)
	FVector MoveOffset;
	UPROPERTY(EditAnywhere)
	float MoveTime = 4.0f;
	
	bool ReachedTarget = false;
	bool ShouldMove = false;
	
	FVector TargetLocation;
	FVector StartingLocation;
};
