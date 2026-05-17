#include "HUDWidget.h"

void UHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UHUDWidget::UpdateHeight(float Height)
{
    

    if (HeightText)
    {
        FString HeightString =
            FString::Printf(TEXT("HEIGHT : %.0fm"), Height);

        HeightText->SetText(FText::FromString(HeightString));
    }
}

void UHUDWidget::UpdateTime(float Time)
{
    if (TimeText)
    {
        int32 Minutes = Time / 60;
        int32 Seconds = (int32)Time % 60;

        FString TimeString =
            FString::Printf(
                TEXT("TIME : %02d:%02d"),
                Minutes,
                Seconds);

        TimeText->SetText(FText::FromString(TimeString));
    }
}

void UHUDWidget::UpdateScore(int32 Score)
{
    if (ScoreText)
    {
        FString ScoreString =
            FString::Printf(
                TEXT("SCORE : %d"),
                Score);

        ScoreText->SetText(
            FText::FromString(ScoreString));
    }
}

void UHUDWidget::UpdateBestScore(int32 BestScore)
{
    if (BestScoreText)
    {
        FString BestScoreString =
            FString::Printf(
                TEXT("BEST : %d"),
                BestScore);

        BestScoreText->SetText(
            FText::FromString(BestScoreString));
    }
}