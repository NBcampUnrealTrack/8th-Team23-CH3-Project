
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "NPC.generated.h"

class USphereComponent;

UCLASS()
class CH3TP23_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	ANPC();

protected:
	virtual void BeginPlay() override;

    // 플레이어 감지용 구체 컴포넌트
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USphereComponent* DetectSphere;

    // 감지 범위 설정 (에디터에서 수정 가능)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
    float DetectRadius;

    // 출력할 대사 목록 (에디터에서 여러 개 입력 가능)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Settings")
    TArray<FString> Dialogues;

    UFUNCTION(BlueprintImplementableEvent, Category = "NPC")
    void OnPlayerApproached(const FString& NPCMessage);

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};

