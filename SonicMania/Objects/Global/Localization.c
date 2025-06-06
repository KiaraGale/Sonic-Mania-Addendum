// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: Localization Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectLocalization *Localization;
static Localization2 localization2;
static Localization3 localization3;
static Localization4 localization4;

void Localization_Update(void) {}

void Localization_LateUpdate(void) {}

void Localization_StaticUpdate(void) {}

void Localization_Draw(void) {}

void Localization_Create(void *data) {}

void Localization_StageLoad(void)
{
    OptionsRAM *options = Options_GetOptionsRAM();
    if (globals->optionsLoaded >= STATUS_OK && options->overrideLanguage) {
        Localization->language = options->language;
        Localization_LoadStrings();
    }
    else {
        Localization->language = sku_language;
        Localization_LoadStrings();
    }
}

void Localization_LoadStrings(void)
{
    RSDK.InitString(&Localization->text, "", 0);

    switch (Localization->language) {
        case LANGUAGE_EN:
            LogHelpers_Print("Loading English strings...");
            RSDK.LoadStringList(&Localization->text, "StringsEN.txt", 16);
            break;

        case LANGUAGE_FR:
            LogHelpers_Print("Loading French strings...");
            RSDK.LoadStringList(&Localization->text, "StringsFR.txt", 16);
            break;

        case LANGUAGE_IT:
            LogHelpers_Print("Loading Italian strings...");
            RSDK.LoadStringList(&Localization->text, "StringsIT.txt", 16);
            break;

        case LANGUAGE_GE:
            LogHelpers_Print("Loading German strings...");
            RSDK.LoadStringList(&Localization->text, "StringsGE.txt", 16);
            break;

        case LANGUAGE_SP:
            LogHelpers_Print("Loading Spanish strings...");
            RSDK.LoadStringList(&Localization->text, "StringsSP.txt", 16);
            break;

        case LANGUAGE_JP:
            LogHelpers_Print("Loading Japanese strings...");
            RSDK.LoadStringList(&Localization->text, "StringsJP.txt", 16);
            break;

#if GAME_VERSION != VER_100
        case LANGUAGE_KO:
            LogHelpers_Print("Loading Korean strings...");
            RSDK.LoadStringList(&Localization->text, "StringsKO.txt", 16);
            break;

        case LANGUAGE_SC:
            LogHelpers_Print("Loading Simp Chinese strings...");
            RSDK.LoadStringList(&Localization->text, "StringsSC.txt", 16);
            break;

        case LANGUAGE_TC:
            LogHelpers_Print("Loading Trad Chinese strings...");
            RSDK.LoadStringList(&Localization->text, "StringsTC.txt", 16);
            break;

        case LANGUAGE_EUS:
            LogHelpers_Print("Loading Euskaran strings...");
            RSDK.LoadStringList(&Localization->text, "StringsEUS.txt", 16);
            break;
#endif

        default: break;
    }

    RSDK.SplitStringList(Localization->strings, &Localization->text, 0, 61);
    RSDK.SplitStringList(localization2.strings, &Localization->text, 62, 126);
    RSDK.SplitStringList(localization3.strings, &Localization->text, 127, 190);
    RSDK.SplitStringList(localization4.strings, &Localization->text, 191, 203);
    Localization->loaded = true;

#if MANIA_USE_EGS
    if (API.CheckAchievementsEnabled()) {
        String *names[STR_STRING_COUNT - STR_ACHIEVEMENT];
        for (int32 i = 0; i < (STR_STRING_COUNT - STR_ACHIEVEMENT); ++i) {
            names[i] = &Localization->strings[i + STR_ACHIEVEMENT];
        }

        API.SetAchievementNames(names, STR_STRING_COUNT - STR_ACHIEVEMENT);
    }
#endif
}

void Localization_GetString(String *string, uint8 id)
{
    memset(string, 0, sizeof(String));
    RSDK.InitString(string, "", 0);

    if (id >= 190)
        RSDK.CopyString(string, &localization4.strings[id - 190]);
    else if (id >= 125 && id <= 189)
        RSDK.CopyString(string, &localization3.strings[id - 126]);
    else if (id >= 61 && id <= 125)
        RSDK.CopyString(string, &localization2.strings[id - 62]);
    else if (id <= 61)
        RSDK.CopyString(string, &Localization->strings[id]);

    for (int32 c = 0; c < string->length; ++c) {
        if (string->chars[c] == '\\')
            string->chars[c] = '\n';
    }
}

void Localization_GetZoneName(String *string, uint8 zone)
{
    switch (zone) {
        case ZONE_GHZ: RSDK.InitString(string, "GREEN HILL", 0); break;
        case ZONE_CPZ: RSDK.InitString(string, "CHEMICAL PLANT", 0); break;
        case ZONE_SPZ: RSDK.InitString(string, "STUDIOPOLIS", 0); break;
        case ZONE_FBZ: RSDK.InitString(string, "FLYING BATTERY", 0); break;
        case ZONE_PGZ: RSDK.InitString(string, "PRESS GARDEN", 0); break;
        case ZONE_SSZ: RSDK.InitString(string, "STARDUST SPEEDWAY", 0); break;
        case ZONE_HCZ: RSDK.InitString(string, "HYDROCITY", 0); break;
        case ZONE_MSZ: RSDK.InitString(string, "MIRAGE SALOON", 0); break;
        case ZONE_OOZ: RSDK.InitString(string, "OIL OCEAN", 0); break;
        case ZONE_LRZ: RSDK.InitString(string, "LAVA REEF", 0); break;
        case ZONE_MMZ: RSDK.InitString(string, "METALLIC MADNESS", 0); break;
        case ZONE_TMZ: RSDK.InitString(string, "TITANIC MONARCH", 0); break;
        case ZONE_ERZ: RSDK.InitString(string, "???", 0); break;
        default: break;
    }
}
void Localization_GetZoneInitials(String *string, uint8 zone)
{
    switch (zone) {
        case ZONE_GHZ: RSDK.InitString(string, "GHZ", 0); break;
        case ZONE_CPZ: RSDK.InitString(string, "CPZ", 0); break;
        case ZONE_SPZ: RSDK.InitString(string, "SPZ", 0); break;
        case ZONE_FBZ: RSDK.InitString(string, "FBZ", 0); break;
        case ZONE_PGZ: RSDK.InitString(string, "PGZ", 0); break;
        case ZONE_SSZ: RSDK.InitString(string, "SSZ", 0); break;
        case ZONE_HCZ: RSDK.InitString(string, "HCZ", 0); break;
        case ZONE_MSZ: RSDK.InitString(string, "MSZ", 0); break;
        case ZONE_OOZ: RSDK.InitString(string, "OOZ", 0); break;
        case ZONE_LRZ: RSDK.InitString(string, "LRZ", 0); break;
        case ZONE_MMZ: RSDK.InitString(string, "MMZ", 0); break;
        case ZONE_TMZ: RSDK.InitString(string, "TMZ", 0); break;
        case ZONE_ERZ: RSDK.InitString(string, "???", 0); break;
        default: break;
    }
}

#if GAME_INCLUDE_EDITOR
void Localization_EditorDraw(void) {}

void Localization_EditorLoad(void) {}
#endif

void Localization_Serialize(void) {}
