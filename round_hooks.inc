#define private stock static
#define callback%0(%1) forward%0(%1);public%0(%1)

callback OnPlayerLeaveDynamicArea(playerid, STREAMER_TAG_AREA:areaid) 
{
    Circle.OnPlayerLeaveDynamicArea(playerid, areaid);
}
#if defined _ALS_OnPlayerLeaveDynamicArea
    #undef OnPlayerLeaveDynamicArea
#else
    #define _ALS_OnPlayerLeaveDynamicArea
#endif
#define OnPlayerLeaveDynamicArea Circle@OnPlayerLeaveDynamicArea

callback OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA:areaid) 
{
    Circle.OnPlayerEnterDynamicArea(playerid, areaid);
}
#if defined _ALS_OnPlayerEnterDynamicArea
    #undef OnPlayerEnterDynamicArea
#else
    #define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea Circle@OnPlayerEnterDynamicArea
