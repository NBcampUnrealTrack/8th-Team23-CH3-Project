#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "T23Character.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UHUDWidget;
struct FInputActionValue;

UCLASS()
class CH3TP23_API AT23Character : public ACharacter
{
	GENERATED_BODY()

public:
	
	AT23Character();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY()
	UHUDWidget* HUDWidget;

	float StartZ;



	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

protected:

	
	
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	void Move(const FInputActionValue& value);
	
	UFUNCTION()
	void StartJump(const FInputActionValue& value);
	
	UFUNCTION()
	void StopJump(const FInputActionValue& value);
	
	UFUNCTION()
	void Look(const FInputActionValue& value);
	
	UFUNCTION()
	void StartSprint(const FInputActionValue& value);
	
	UFUNCTION()
	void StopSprint(const FInputActionValue& value);

	void Interact();
	void StartCrouch();
	void StopCrouch();
	

private:
	float SprintSpeed; 
	float NormalSpeed;
	float SprintSpeedMultiplier;
	float ElapsedTime;

	int32 CurrentScore;
	int32 BestScore;
	
	
};

