#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileGrid.generated.h"

class ATile;
class UTextRenderComponent;

UCLASS()
class SPLITBEAN_API ATileGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	ATileGrid();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	int32 Columns = 7;
	UPROPERTY(EditAnywhere)
	int32 Rows = 12;
	UPROPERTY(EditAnywhere)
	float TileSize = 100.0f;
	
	UPROPERTY(EditAnywhere)
	TArray<FVector2D> SafeTiles;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ATile> TileClass;
	UPROPERTY(EditAnywhere)
	AActor* SpawnPoint;
	UPROPERTY(EditAnywhere)
	UTextRenderComponent* MapDisplay;
	
private:
	TArray<ATile*> SpawnedTiles;
	void SpawnGrid();
	void DrawMapOnWall();
};
