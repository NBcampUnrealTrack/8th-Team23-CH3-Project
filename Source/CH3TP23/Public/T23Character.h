//T23Character.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "T23Character.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UHUDWidget;
class UInputAction;
class USpotLightComponent; //스포트라이트 선언
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light")
	USpotLightComponent* HeadLightComp;
	//헤드라이트 컴포넌트 선언

	UFUNCTION(BlueprintCallable, Category = "Light")
	void SetHeadlightEnabled(bool bIsNight);
	//밤낮에 변화에 따른 헤드라이트on/off

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* PauseAction;

	UPROPERTY()
	UUserWidget* PauseWidget;

	UPROPERTY()
	UHUDWidget* HUDWidget;

	float StartZ;

	// 포탈 탑승 후 점수 계산 시작
	void StartScoreSystem();
	//
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

	UFUNCTION(BlueprintCallable)
	void TogglePauseMenu();

	void Interact();
	void StartCrouch();
	void StopCrouch();
	
private:

	float SprintSpeed;
	float NormalSpeed;
	float SprintSpeedMultiplier;
	float ElapsedTime;

	// 점수 계산 가능 여부
	bool bCanCalculateScore;
	//
	int32 CurrentScore;
	int32 BestScore;
};