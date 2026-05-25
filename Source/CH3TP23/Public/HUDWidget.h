//HUDWidget.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "HUDWidget.generated.h"

UCLASS()
class CH3TP23_API UHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    virtual void NativeConstruct() override;

    void UpdateHeight(float Height);

    void UpdateTime(float Time);

    void UpdateScore(int32 Score);

    void UpdateBestScore(int32 BestScore);

protected:

    UPROPERTY(meta = (BindWidget))
    UTextBlock* HeightText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TimeText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ScoreText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* BestScoreText;


};