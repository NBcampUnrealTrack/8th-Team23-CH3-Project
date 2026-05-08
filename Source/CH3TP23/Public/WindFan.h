// WindFan.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WindFan.generated.h"

UCLASS()
class CH3TP23_API AWindFan : public AActor
{
	GENERATED_BODY()
	
public:	
	AWindFan();
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wind|Components")
	USceneComponent* SceneRoot;
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* WindArea;

	UPROPERTY(EditAnywhere, Category = "Wind")
	float WindStrength = 10.f;

};
