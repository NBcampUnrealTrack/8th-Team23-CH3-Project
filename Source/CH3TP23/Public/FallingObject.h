//FallingObject.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FallingObject.generated.h"

UCLASS()
class CH3TP23_API AFallingObject : public AActor
{
	GENERATED_BODY()
	
public:	
	AFallingObject();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FallingObject|Components")
	class USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FallingObject|Components")
	class UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FallingObject|Assets")
	class UMaterialInterface* MaterialAssets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FallingObject|Assets")
	class UStaticMesh* MeshAsset;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
