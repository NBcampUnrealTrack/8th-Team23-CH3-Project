#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "T23PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
UCLASS()
class CH3TP23_API AT23PlayerController : public APlayerController
{
	GENERATED_BODY()

public: 
	AT23PlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* SprintAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

protected:
	virtual void BeginPlay() override;
};
