// Fall.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fall.generated.h"

UCLASS()
class CH3TP23_API AFall : public AActor
{
	GENERATED_BODY()
	
public:	
	AFall();
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fall|Components")
	USceneComponent* SceneRoot;
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AActor> ActorClassToSpawn;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float SpawnInterval = 0.5f; //스폰 간격

	float Timer = 0.f; //스폰 시간
};

