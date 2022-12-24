#pragma once

#include "game_info.h"
#include "Blueprint/UserWidget.h"
#include "sword_skill_cooltime_ui.generated.h"

UCLASS()
class SPACE_COIN_API Usword_skill_cooltime_ui : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UProgressBar* ultimate_skill_bar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UProgressBar* defense_skill_bar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UProgressBar* slash_skill_bar;

public:
	virtual void NativeConstruct() override;
	UFUNCTION()
		void UpdateUltimateCooltime(float cooltime);
	UFUNCTION()
		void UpdateDefenseCooltime(float cooltime);
	UFUNCTION()
		void UpdateSlashCooltime(float cooltime);
};