#pragma once

#include "game_info.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "notify_attackstart.generated.h"

UCLASS()
class SPACE_COIN_API Unotify_attackstart : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual FString GetNotifyName_Implementation() const override;

private:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
