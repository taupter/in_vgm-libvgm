#ifndef __PLAYCFG_HPP__
#define __PLAYCFG_HPP__

#include <stdtype.h>
#include <string>
#include <vector>
#include <array>

#include <emu/EmuStructs.h>	// for DEV_ID

struct GeneralOptions
{
	UINT32 smplRate;
	UINT8 smplBits;
	UINT32 pbRate;
	double volume;
	double pbSpeed;
	UINT32 maxLoops;
	
	UINT8 resmplMode;
	UINT8 chipSmplMode;
	UINT32 chipSmplRate;
	
	UINT32 fadeTime;
	UINT32 pauseTime_jingle;
	UINT32 pauseTime_loop;
	
	bool pseudoSurround;
	bool preferJapTag;
	bool showDevCore;
	UINT8 hardStopOld;
	
	bool immediateUpdate;
	bool resetMuting;
	bool noInfoCache;
	std::string titleFormat;
	bool appendFM2413;
	bool trimWhitespace;
	bool stdSeparators;
	bool fidTagFallback;	// Jap/Eng tag fallback for file info dialogue
	UINT32 mediaLibFileType;
	struct
	{
		bool vgm;
		bool s98;
		bool dro;
		bool gym;
	} fileTypes;
};
struct ChipOptions
{
	const char* cfgEntryName;
	DEV_ID chipType;
	DEV_ID chipTypeSub;
	UINT8 chipInstance;
	UINT8 chipDisable;	// bit mask, bit 0 (01) = main, bit 1 (02) = linked
	UINT8 emuTypeID;	// emuType affects emuCore[emuTypeID]
	UINT8 corePanMask[2];	// sound cores that allow for panning (bit 0 = 1st core, bit 1 = 2nd core, ...)
	UINT32 emuCore[2];
	UINT16 muteChnCnt[2];
	UINT16 panChnCnt[2];
	UINT32 muteMask[2];
	INT16 panMask[2][32];	// scale: -0x100 .. 0 .. +0x100
	UINT32 addOpts;
};
struct PluginConfig
{
	GeneralOptions genOpts;
	std::vector< std::array<ChipOptions, 2> > chipOpts;
};

class PlayerA;


UINT32 EmuTypeNum2CoreFCC(UINT8 chipType, UINT8 emuType);
UINT8 CoreFCC2EmuTypeNum(UINT8 chipType, UINT32 coreFCC);

void LoadConfiguration(PluginConfig& pCfg, const char* iniFileName);
void SaveConfiguration(const PluginConfig& pCfg, const char* iniFileName);

void ApplyCfg_General(PlayerA& player, const GeneralOptions& opts, bool noLiveOpts = false);
void ApplyCfg_Chip(PlayerA& player, const GeneralOptions& gOpts, const ChipOptions& cOpts);

#endif	// __PLAYCFG_HPP__
