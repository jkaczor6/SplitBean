#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SplitBeanPlayerCharacter.generated.h"

class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class UMaterial;
struct FInputActionValue;

UCLASS()
class SPLITBEAN_API ASplitBeanPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASplitBeanPlayerCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveInput(const FInputActionValue& Value);
	void LookInput(const FInputActionValue& Value);
	void JumpInputStart(const FInputActionValue& Value);
	void JumpInputEnd(const FInputActionValue& Value);
	void UseInput(const FInputActionValue& Value);
	
	void SwitchTeams(int32 NewTeamIndex);
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere, Category = "Bean")
	UMaterial* DefaultMaterial;
	UPROPERTY(EditAnywhere, Category = "Bean")
	UMaterial* RedMaterial;
	UPROPERTY(EditAnywhere, Category = "Bean")
	UMaterial* BlueMaterial;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* IMC;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* UseAction;
	
	UPROPERTY(VisibleAnywhere)
	int32 TeamIndex = 0;
};
