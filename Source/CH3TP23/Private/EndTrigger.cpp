#include "EndTrigger.h"

#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

AEndTrigger::AEndTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision =
		CreateDefaultSubobject<UBoxComponent>(
			TEXT("BoxCollision"));

	RootComponent = BoxCollision;
}

void AEndTrigger::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(
		this,
		&AEndTrigger::OnOverlapBegin);
}

void AEndTrigger::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (EndingWidgetClass)
		{
			UUserWidget* EndingWidget =
				CreateWidget<UUserWidget>(
					GetWorld(),
					EndingWidgetClass);

			if (EndingWidget)
			{
				EndingWidget->AddToViewport();

				APlayerController* PlayerController =
					GetWorld()->GetFirstPlayerController();

				if (PlayerController)
				{
					PlayerController->bShowMouseCursor = true;

					FInputModeUIOnly InputMode;

					PlayerController->SetInputMode(InputMode);
				}
			}
		}
	}
}

