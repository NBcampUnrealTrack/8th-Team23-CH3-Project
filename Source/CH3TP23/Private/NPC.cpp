
#include "NPC.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

ANPC::ANPC()
{
    PrimaryActorTick.bCanEverTick = false;

    // 기본 감지 반경 설정
    DetectRadius = 300.0f;

    // 구체 컴포넌트 생성 및 루트에 부착
    DetectSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectSphere"));
    DetectSphere->SetupAttachment(RootComponent);
    DetectSphere->SetSphereRadius(DetectRadius);

    // 충돌 프로필 설정 (겹침 감지만 가능하도록)
    DetectSphere->SetCollisionProfileName(TEXT("Trigger"));
}

void ANPC::BeginPlay()
{
	Super::BeginPlay();

    DetectSphere->OnComponentBeginOverlap.AddDynamic(this, &ANPC::OnOverlapBegin);
    DetectSphere->OnComponentEndOverlap.AddDynamic(this, &ANPC::OnOverlapEnd);

    // 기본 대사 예시 (코드로 넣어두거나 에디터에서 변경 가능)
    if (Dialogues.Num() == 0)
    {
        Dialogues.Add(TEXT("이 근처에 하늘섬으로 올라가는 길이 있다고 하더라고요?"));
        Dialogues.Add(TEXT("하늘섬에 가면 소원을 이루어준다는 전설이 있어요."));
    }
}

void ANPC::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

    if (OtherActor && (OtherActor == PlayerCharacter))
    {
        if (Dialogues.Num() > 0)
        {
            int32 RandomIndex = FMath::RandRange(0, Dialogues.Num() - 1);
            FString SelectedDialogue = Dialogues[RandomIndex];

            // 로그 및 화면 출력
            UE_LOG(LogTemp, Warning, TEXT("NPC: %s"), *SelectedDialogue);
            GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, FString::Printf(TEXT("NPC: %s"), *SelectedDialogue));

            // 블루프린트로 대사 전달 (UI 띄우기용 이벤트 호출)
            OnPlayerApproached(SelectedDialogue);
        }
    }
}

void ANPC::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

    if (OtherActor && (OtherActor == PlayerCharacter))
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Silver, TEXT("(플레이어가 멀어졌습니다)"));
    }
}

