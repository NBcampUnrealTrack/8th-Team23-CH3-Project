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
	class USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fall|Components")
	class UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fall|Assets")
	class UMaterialInterface* MaterialAssets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fall|Assets")
	class UStaticMesh* MeshAsset;

	UPROPERTY(VisibleAnywhere, Category = "SpawnArea")
	class UBoxComponent* SpawnArea;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AActor> ActorClassToSpawn;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float SpawnInterval = 5.0f; //스폰 간격

	float Timer = 0.0f; //스폰 시간
};

