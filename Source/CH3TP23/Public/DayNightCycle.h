#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DayNightCycle.generated.h"

class UDirectionalLightComponent;

UCLASS()
class CH3TP23_API ADayNightCycle : public AActor
{
    GENERATED_BODY()

public:
    
    ADayNightCycle();

    // 기존 태양 라이트 아래에 달 라이트 추가
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lighting")
    UDirectionalLightComponent* MoonLight;

    //태양 역할을 할 디렉셔널 라이트 컴포넌트 선언
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lighting")
    UDirectionalLightComponent* SunLight;

    //에디터에서 직접 수정할 수 있는 회전 속도 변수
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting")
    float RotationSpeed;

    // 부드러운 밝기 전환을 위한 추가 변수들

    // 지평선 근처에서 서서히 어두워지기 시작할 각도 (음수면 지평선 위, 양수면 지평선 아래)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting|Transition")
    float FadeStartPitch;

    // 완전히 빛이 꺼지는 각도
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting|Transition")
    float FadeEndPitch;

    // 낮 시간의 최대 태양 밝기
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting|Transition")
    float MaxSunIntensity;

    // 밤 시간의 최대 달 밝기
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting|Transition")
    float MaxMoonIntensity;

    virtual void Tick(float DeltaTime) override;

protected:
    
    virtual void BeginPlay() override;

private:
    // 현재 회전 각도를 저장할 변수 추가
    float CurrentRotationAngle = -90.0f;
};