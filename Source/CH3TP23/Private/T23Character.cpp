//T23Character.cpp

#include "T23Character.h"
#include "T23PlayerController.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/SpotLightComponent.h"
#include "T23Interface.h"
#include "HUDWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


AT23Character::AT23Character()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	//조명 생성 및 설정
	HeadLightComp = CreateDefaultSubobject<USpotLightComponent>(TEXT("HeadLight"));
	HeadLightComp->SetupAttachment(CameraComp);

	HeadLightComp->Intensity = 3000.0f;          // 빛의 밝기
	HeadLightComp->AttenuationRadius = 3000.0f;  // 빛이 도달하는 최대 거리
	HeadLightComp->InnerConeAngle = 30.0f;       // 안쪽 밝은 빛의 각도
	HeadLightComp->OuterConeAngle = 45.0f;       // 바깥쪽 퍼지는 빛의 각도
	// 조명 위치 미세 조정
	HeadLightComp->SetRelativeLocation(FVector(30.0f, 0.0f, 0.0f));

	NormalSpeed = 250.0f;

	SprintSpeedMultiplier = 2.0f;

	SprintSpeed = NormalSpeed * SprintSpeedMultiplier;

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;

	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	ElapsedTime = 0.f;

	BestScore = 0;

	CurrentScore = 0;

	// 처음에는 점수 계산 안함
	bCanCalculateScore = false;
}

void AT23Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput =
		Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AT23PlayerController* PlayerController =
			Cast<AT23PlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&AT23Character::Move
				);
			}

			if (PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Triggered,
					this,
					&AT23Character::StartJump
				);

				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Completed,
					this,
					&AT23Character::StopJump
				);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&AT23Character::Look
				);
			}

			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Triggered,
					this,
					&AT23Character::StartSprint
				);

				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Completed,
					this,
					&AT23Character::StopSprint
				);
			}

			if (PlayerController->InteractAction)
			{
				EnhancedInput->BindAction(
					PlayerController->InteractAction,
					ETriggerEvent::Started,
					this,
					&AT23Character::Interact
				);
			}

			if (PlayerController->CrouchAction)
			{
				EnhancedInput->BindAction(
					PlayerController->CrouchAction,
					ETriggerEvent::Started,
					this,
					&AT23Character::StartCrouch
				);

				EnhancedInput->BindAction(
					PlayerController->CrouchAction,
					ETriggerEvent::Completed,
					this,
					&AT23Character::StopCrouch
				);
			}
				EnhancedInput->BindAction(
				PauseAction,
				ETriggerEvent::Started,
				this,
				&AT23Character::TogglePauseMenu);
		}
	}
}

void AT23Character::Move(const FInputActionValue& value)
{
	if (!Controller) return;

	const FVector2D MoveInput = value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}

	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}

void AT23Character::StartJump(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		Jump();
	}
}

void AT23Character::StopJump(const FInputActionValue& value)
{
	if (!value.Get<bool>())
	{
		StopJumping();
	}
}

void AT23Character::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

void AT23Character::StartSprint(const FInputActionValue& value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void AT23Character::StopSprint(const FInputActionValue& value)
{
	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
}

void AT23Character::Interact()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			2.f,
			FColor::Red,
			TEXT("Press E ")
		);
	}

	FVector Start = CameraComp->GetComponentLocation();

	FVector End =
		Start + (CameraComp->GetForwardVector() * 300.f);

	FHitResult Hit;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_Visibility,
		Params
	);

	if (bHit && Hit.GetActor())
	{
		if (Hit.GetActor()->Implements<UT23Interface>())
		{
			IT23Interface::Execute_Interact(Hit.GetActor());
		}
	}
}

void AT23Character::StartCrouch()
{
	Crouch();
}

void AT23Character::StopCrouch()
{
	UnCrouch();
}

void AT23Character::BeginPlay()
{
	Super::BeginPlay();

	StartZ = GetActorLocation().Z;

	APlayerController* PlayerController =
		GetWorld()->GetFirstPlayerController();

	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = false;

		FInputModeGameOnly InputMode;

		PlayerController->SetInputMode(InputMode);
	}

	if (HUDWidgetClass)
	{
		HUDWidget =
			CreateWidget<UHUDWidget>(
				GetWorld(),
				HUDWidgetClass);

		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}
}

void AT23Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 포탈 타기 전에는 계산 안함
	if (!bCanCalculateScore)
	{
		return;
	}
	//
	ElapsedTime += DeltaTime;

	float CurrentZ = GetActorLocation().Z;

	float Height =
		(CurrentZ - StartZ) / 100.f;

	Height = FMath::Max(0.f, Height);

	CurrentScore = Height * 10;

	BestScore = FMath::Max(
		BestScore,
		CurrentScore);

	if (HUDWidget)
	{
		HUDWidget->UpdateHeight(Height);

		HUDWidget->UpdateTime(ElapsedTime);

		HUDWidget->UpdateScore(CurrentScore);

		HUDWidget->UpdateBestScore(BestScore);
	}
}

void AT23Character::StartScoreSystem()
{
	if (bCanCalculateScore) //딱 한번만
	{
		return; 
	}

	bCanCalculateScore = true;

	StartZ = GetActorLocation().Z;

	CurrentScore = 0;

	ElapsedTime = 0.f;

}

void AT23Character::TogglePauseMenu()
{
	APlayerController* PlayerController =
		GetWorld()->GetFirstPlayerController();

	if (!PlayerController) return;

	bool bIsPaused =
		UGameplayStatics::IsGamePaused(GetWorld());

	if (!bIsPaused)
	{
		UGameplayStatics::SetGamePaused(
			GetWorld(),
			true);

		if (PauseWidgetClass)
		{
			PauseWidget =
				CreateWidget<UUserWidget>(
					GetWorld(),
					PauseWidgetClass);

			if (PauseWidget)
			{
				PauseWidget->AddToViewport();
			}
		}

		PlayerController->bShowMouseCursor = true;

		FInputModeUIOnly InputMode;

		PlayerController->SetInputMode(InputMode);
	}
	else
	{
		UGameplayStatics::SetGamePaused(
			GetWorld(),
			false);

		if (PauseWidget)
		{
			PauseWidget->RemoveFromParent();
		}

		PlayerController->bShowMouseCursor = false;

		FInputModeGameOnly InputMode;

		PlayerController->SetInputMode(InputMode);
	}
}

//밤낮에 변화에 따른 헤드라이트on/off
void AT23Character::SetHeadlightEnabled(bool bIsNight)
{
	if (HeadLightComp)
	{
		HeadLightComp->SetVisibility(bIsNight);
	}
}