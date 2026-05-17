#include "T23Character.h"
#include "T23PlayerController.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "T23Interface.h"
#include "HUDWidget.h"
#include "Blueprint/UserWidget.h"


AT23Character::AT23Character()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;


	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	 
	
	 NormalSpeed = 250.0f;
	
	 SprintSpeedMultiplier = 2.0f;
	 
	 SprintSpeed = NormalSpeed * SprintSpeedMultiplier;

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;

	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	PrimaryActorTick.bCanEverTick = true;

	ElapsedTime = 0.f;

	BestScore = 0;

}


void AT23Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AT23PlayerController* PlayerController = Cast<AT23PlayerController>(GetController()))
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

