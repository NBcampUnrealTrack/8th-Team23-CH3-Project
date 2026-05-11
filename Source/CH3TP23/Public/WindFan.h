// WindFan.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WindFan.generated.h"

UENUM(BlueprintType)
enum class EWindType : uint8
{
	Constant UMETA(DisplayName = "WindFan"),
	Bounce UMETA(DisplayName = "BouncyBoll"),
	Both UMETA(DisplayName = "All")
};

UCLASS()
class CH3TP23_API AWindFan : public AActor
{
	GENERATED_BODY()
	
public:	
	AWindFan();
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WindFan|Components")
	class USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WindFan|Components")
	class UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WindFan|Assets")
	class UMaterialInterface* MaterialAssets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WindFan|Assets")
	class UStaticMesh* MeshAsset;

	UPROPERTY(VisibleAnywhere, Category = "Wind | Components")
	class UBoxComponent* WindArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wind|Settings")
	EWindType WindType = EWindType::Constant;

	UPROPERTY(EditAnywhere, Category = "Wind|Settings")
	float ConstantStrength = 500.0f;

	UPROPERTY(EditAnywhere, Category = "Wind|Settings")
	float BounceStrength = 2500.0f;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp
		, AActor* OtherActor
		, UPrimitiveComponent* OtherComp
		, int32 OtherBodyIndex
		, bool bFromSweep
		, const FHitResult& SweepResult);

};
