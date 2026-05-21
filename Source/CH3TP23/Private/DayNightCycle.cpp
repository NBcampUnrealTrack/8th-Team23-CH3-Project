#include "DayNightCycle.h"
#include "Components/DirectionalLightComponent.h" 


ADayNightCycle::ADayNightCycle()
{
    PrimaryActorTick.bCanEverTick = true;

    SunLight = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("SunLight"));
    RootComponent = SunLight;
    SunLight->SetMobility(EComponentMobility::Movable);
    SunLight->AtmosphereSunLightIndex = 0;
    SunLight->ForwardShadingPriority = 1;

    MoonLight = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("MoonLight"));
    MoonLight->SetupAttachment(RootComponent);
    MoonLight->SetMobility(EComponentMobility::Movable);
    MoonLight->SetRelativeRotation(FRotator(180.0f, 0.0f, 0.0f));

    //태양과 달의 우선순위에 관련
    MoonLight->bAtmosphereSunLight = true;
    MoonLight->AtmosphereSunLightIndex = 1;
    MoonLight->ForwardShadingPriority = 0;
    //

    RotationSpeed = 10.0f;
    MaxSunIntensity = 10.0f;
    MaxMoonIntensity = 2.0f;

    // 지평선(-10도)부터 서서히 어두워져서, 지평선 아래(5도)가 되면 완전히 꺼지게 설정
    FadeStartPitch = -10.0f;
    FadeEndPitch = 5.0f;

    SunLight->SetIntensity(MaxSunIntensity);
    MoonLight->SetIntensity(MaxMoonIntensity);

    // 초기 각도 설정 (-90도는 정오를 의미)
    CurrentRotationAngle = -90.0f;
}

void ADayNightCycle::BeginPlay()
{
    Super::BeginPlay();
   
    SunLight->SetRelativeRotation(FRotator(CurrentRotationAngle, 0.0f, 0.0f));
}

void ADayNightCycle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CurrentRotationAngle += RotationSpeed * DeltaTime;

    // 각도 값이 무한히 커지는 것을 방지 (플로팅 포인트 정밀도 유지)
    if (CurrentRotationAngle >= 360.0f)
    {
        CurrentRotationAngle -= 360.0f;
    }

    // 누적된 절대 각도를 덮어씌움
    SunLight->SetRelativeRotation(FRotator(CurrentRotationAngle, 0.0f, 0.0f));

    if (SunLight != nullptr && MoonLight != nullptr)
    {
        // 현재 태양과 달의 Pitch 가져오기
        float SunPitch = SunLight->GetComponentRotation().Pitch;
        float MoonPitch = MoonLight->GetComponentRotation().Pitch;

        // 태양빛 서서히 조절 (MapRangeClamped 적용)
        float CurrentSunIntensity = FMath::GetMappedRangeValueClamped(
            FVector2D(FadeStartPitch, FadeEndPitch),
            FVector2D(MaxSunIntensity, 0.0f),
            SunPitch);

        // 달빛 서서히 조절 (태양과 동일한 로직 적용)
        float CurrentMoonIntensity = FMath::GetMappedRangeValueClamped(
            FVector2D(FadeStartPitch, FadeEndPitch),
            FVector2D(MaxMoonIntensity, 0.0f),
            MoonPitch);
           
        MoonLight->SetIntensity(CurrentMoonIntensity);
    }
}
