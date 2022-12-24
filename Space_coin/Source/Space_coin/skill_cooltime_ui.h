#pragma once

#include "game_info.h"
#include "Blueprint/UserWidget.h"
#include "skill_cooltime_ui.generated.h"

UCLASS()
class SPACE_COIN_API Uskill_cooltime_ui : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UProgressBar* dash_skill_bar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UProgressBar* sniper_skill_bar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UProgressBar* launcher_skill_bar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UProgressBar* missile_skill_bar;
public:
	virtual void NativeConstruct() override;
	UFUNCTION()
		void UpdateDashCooltime(float cooltime);
	UFUNCTION()
		void UpdateLauncherCooltime(float cooltime);
	UFUNCTION()
		void UpdateSniperCooltime(float cooltime);
	UFUNCTION()
		void UpdateMissileCooltime(float cooltime);


};
