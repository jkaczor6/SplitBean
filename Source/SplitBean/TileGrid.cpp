#include "TileGrid.h"
#include "Tile.h"
#include "Components/TextRenderComponent.h"

ATileGrid::ATileGrid()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	MapDisplay = CreateDefaultSubobject<UTextRenderComponent>(TEXT("MapDisplay"));
	MapDisplay->SetupAttachment(RootComponent);
	MapDisplay->SetWorldSize(35.f);
	MapDisplay->SetHorizontalAlignment(EHTA_Left);
}

void ATileGrid::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		SpawnGrid();
	}
	
	DrawMapOnWall();
}

void ATileGrid::SpawnGrid()
{
	for (int32 Row = 0; Row < Rows; Row++)
	{
		for (int32 Col = 0; Col < Columns; Col++)
		{
			float TileSpacing = TileSize + 10.0f;
			FVector Location = GetActorLocation() + FVector(-Row * TileSpacing, -Col * TileSpacing, 0.0f);
			ATile* NewTile = GetWorld()->SpawnActor<ATile>(TileClass, Location, FRotator::ZeroRotator);
			if (!NewTile) continue;
			
			NewTile->IsSafe = SafeTiles.Contains(FVector2D(Col,Row));
			NewTile->SpawnPoint = SpawnPoint;
			
			SpawnedTiles.Add(NewTile);
		}
	}
}

void ATileGrid::DrawMapOnWall()
{
	FString Map = TEXT("");
	
	for (int32 Row = Rows - 1; Row >= 0; Row--)
	{
		for (int32 Col = 0; Col < Columns; Col++)
		{
			bool Safe = SafeTiles.Contains(FVector2D(Col, Row));
			Map += Safe ? TEXT("O ") : TEXT("X ");
		}
		Map += TEXT("\n");
	}
	
	MapDisplay->SetText(FText::FromString(Map));
}
