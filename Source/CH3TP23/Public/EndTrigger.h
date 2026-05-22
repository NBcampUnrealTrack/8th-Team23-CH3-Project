#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndTrigger.generated.h"

class UBoxComponent;
class UUserWidget;

UCLASS()
class CH3TP23_API AEndTrigger : public AActor
{
	GENERATED_BODY()

public:
	AEndTrigger();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> EndingWidgetClass;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};