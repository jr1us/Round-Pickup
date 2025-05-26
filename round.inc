/*
*
*   - Author: jrius (vk.com/s.fridom & t.me/dcapybarov & github.com/jr1us) -
*   - Include: Round Pickup - 
*   - Модуль разработан на версии компилятора 3.10.8 -
*
*   - Модуль предоставляет следующие функции:
*
*
*       * Circle.CreateObject(modelId, Float:X, Float:Y, Float:Z, Float:Angle, worldId = 0, interiorId = 0, Float:distance = 0.8, color = 0, area = 0, Float:AreaSize = 2.0,  player_id = Circle@INVALID_PLAYER_ID, text3d[] = "", Float:drawdistance = 10.0, position = 2) 
*           [!] Создает круглый объект в виде пикапа ;
*           -  Включить динамическую зону: .area = 1 ;
*           -  Сменить размер: .position = от 0 до 2 ;
*           -  Cменить цвет объекта: .color = от 0 до 9;
*       
*       * Circle.CreateActor(modelId, Float:X, Float:Y, Float:Z, Float:Angle, worldId = 0, interiorId = 0, Float:distance = 0.8, color = 0, area = 0, Float:AreaSize = 2.0, player_id = Circle@INVALID_PLAYER_ID, text3d[] = "", Float:drawdistance = 10.0, position = 2) 
*           [!] Создает актера и перед ним создает круглый пикап.
*           -  Включить динамическую зону: .area = 1 ;
*           -  Сменить размер: .position = от 0 до 2 ;
*           -  Cменить цвет объекта: .color = от 0 до 9;
*       
*       * В модуле добавлены макросы:
*           - private: stock static - Это является функцией / переменной, которая не будет передана никуда кроме данного модуля.
*           - callback: forward & public - Удобный формат публичных функций
*
*       * К сожаления я не понял почему у меня не хочет хукаться каллбек: OnGameModeInit
*       * Поэтому его нужно будет вызвать для Init.
*       * Добавьте к себе в OnGameModeInit куда угодно: Circle.Init();
*
*
*       * Возможно буду обновлять, пока идей нет.
*       * Можете предлагать: vk.com/s.fridom & t.me/dcapybarov & github.com/jr1us
*
*       * Модуль изначально создавался для моих проектов, но я решил им поделиться.
*       * Стилистика кода, возможна отпугнет кого-то, но мне как то все равно :)
*       * Есть немного примеров с работой данного модуля включить тест режим - #define Circle@Test 1
*/

#if defined Circle
   #undef Circle
#endif
#define Circle. _Circle

#if defined this
   #undef this
#endif
#define this. _Circle

#define Circle@Test 0

#if !defined RoundHooks
    #include <round_hooks>
#else
    #include ../dev/round_hooks
#endif

#define MAX_CIRCLE_OBJECT 1000

#define Circle@INVALID_PLAYER_ID -1
#define Circle@INVALID_CREATE_SLOT_ID -1
#define Circle@INVALID_AREA_ID -1

private Circle.ColorName[][16] = {"black", "blue", "green", "grey", "lightblue", "samporange", "red-2", "red-3", "white",  "yellow"};
private Float:Circle.Position[] =
{
    1.6844, 1.7844, 1.8844
};

enum Circle.obj_data {
    STREAMER_TAG_OBJECT:Circle.ObjectId,
    STREAMER_TAG_3D_TEXT_LABEL:Circle.TextId,
    STREAMER_TAG_AREA:Circle.AreaId,
    STREAMER_TAG_ACTOR:Circle.ActorId
}

private Circle.cData[MAX_CIRCLE_OBJECT][this.obj_data];
private Circle.GetFreeSlots() {

    for new i; i < MAX_CIRCLE_OBJECT; i++ do
        if (this.cData[i][this.ObjectId] == INVALID_OBJECT_ID) return i;

    return INVALID_OBJECT_ID;
}

callback Circle.Init() {
    for new i; i < MAX_CIRCLE_OBJECT; i++ do
    {
        this.cData[i][this.ObjectId] = INVALID_OBJECT_ID;
        this.cData[i][this.AreaId] = Circle@INVALID_AREA_ID;
        this.cData[i][this.TextId] = STREAMER_TAG_3D_TEXT_LABEL:INVALID_3DTEXT_ID;
        this.cData[i][this.ActorId] = STREAMER_TAG_ACTOR:INVALID_ACTOR_ID;
    }

    #if defined Circle@Test
    new objectId;

    objectId = this.CreateObject(1961.2102, 1345.3186, 15.3746,   .position = 0, .color = random(sizeof this.ColorName), .area = 1, .text3d = "Area\nALT", .AreaSize = 0.5);
    printf("[Test #1] Create Round Pickup: %d", objectId);

    objectId = this.CreateObject(1958.9615, 1345.4948, 15.3746,   .position = 1, .color = random(sizeof this.ColorName), .text3d = "Area\nCTRL", .area = 1);
    printf("[Test #2] Create Round Pickup: %d", objectId);

    objectId = this.CreateObject(1956.6694, 1345.0942, 15.3746,   .position = 2, .color = random(sizeof this.ColorName), .area = 1, .text3d = "Area\nH");
    printf("[Test #3] Create Round Pickup: %d", objectId);

    printf("[Circle] init include. (Max Circle: %d)", MAX_CIRCLE_OBJECT);

    this.CreateActor(70, 1954.9333,1340.5778,15.3746,294.1870);
    this.CreateActor(112, 1957.6589,1340.3300,15.3746,355.4700);
    this.CreateActor(285, 1961.1416,1340.9841,15.3746,75.5034);

    this.CreateActor(70, 1952.8512,1342.3278,15.3672,163.4581);
    this.CreateActor(112, 1954.3223,1344.5653,15.3746,330.3032);
    this.CreateActor(285, 1952.7118,1345.4561,15.3672,72.0748);
    #endif
}

stock Circle.CreateActor(modelId, Float:X, Float:Y, Float:Z, Float:Angle, worldId = 0, interiorId = 0, Float:distance = 0.8, color = 0, area = 0, Float:AreaSize = 2.0,
    player_id = Circle@INVALID_PLAYER_ID, text3d[] = "", Float:drawdistance = 10.0, position = 2) {   

    new Float:objX = X + (distance * floatsin(-Angle, degrees));
    new Float:objY = Y + (distance * floatcos(-Angle, degrees));

    new slotId = this.CreateObject(objX, objY, Z, worldId, interiorId, color, area, AreaSize, player_id, text3d, drawdistance, position);

    if (slotId == INVALID_OBJECT_ID) {
        printf("[CreateActor] dont create actor -> %d | X: %2.f | Y: %2.f | Z: %2.f | objX: %2.f | objY: %2.f", modelId, X, Y, Z, objX, objY);
        return Circle@INVALID_CREATE_SLOT_ID;
    }
    
    this.cData[slotId][this.ActorId] = CreateDynamicActor(modelId, X, Y, Z, Angle);

    return slotId;
}

stock Circle.CreateObject(Float:X, Float:Y, Float:Z, worldId = 0, interiorId = 0, color = 0, area = 0, Float:AreaSize = 2.0,
    player_id = Circle@INVALID_PLAYER_ID, text3d[] = "", Float:drawdistance = 10.0, position = 2) {
    
    new slotId = this.GetFreeSlots();

    if (slotId == INVALID_OBJECT_ID) 
        return Circle@INVALID_CREATE_SLOT_ID;

    this.cData[slotId][this.ObjectId] = CreateDynamicObject(1317, X, Y, Z - this.Position[position], 0.0, 0.0, 0.0, .worldid = worldId, .interiorid = interiorId ,.playerid = player_id);
    SetDynamicObjectMaterial(this.cData[slotId][this.ObjectId], 0, 18646, "matcolours", this.ColorName[color], 0xFFFFFFFF);

    if (area) 
        this.cData[slotId][this.AreaId] = CreateDynamicCylinder(X, Y, Z, Z + 1.0, AreaSize, worldId, interiorId, .playerid = player_id);
    
    if (strlen(text3d)) 
        this.cData[slotId][this.TextId] = CreateDynamic3DTextLabel(text3d, -1, X, Y, Z, drawdistance, .worldid = worldId, .interiorid = interiorId, .playerid = player_id);
    
    return slotId;
}

stock Circle.DestroyObject(slotId) {
    if (this.cData[slotId][this.ObjectId] != INVALID_OBJECT_ID) {
        DestroyDynamicObject(this.cData[slotId][this.ObjectId]);

        this.cData[slotId][this.ObjectId] = INVALID_OBJECT_ID;
    }

    if (this.cData[slotId][this.TextId] != STREAMER_TAG_3D_TEXT_LABEL:INVALID_3DTEXT_ID) {
        DestroyDynamic3DTextLabel(this.cData[slotId][this.TextId]);

        this.cData[slotId][this.TextId] = STREAMER_TAG_3D_TEXT_LABEL:INVALID_3DTEXT_ID;
    }

    if (this.cData[slotId][this.AreaId] != Circle@INVALID_AREA_ID) {
        DestroyDynamicArea(this.cData[slotId][this.AreaId]);

        this.cData[slotId][this.AreaId] = Circle@INVALID_AREA_ID;
    }

    if (this.cData[slotId][this.ActorId] != STREAMER_TAG_ACTOR:INVALID_ACTOR_ID) {
        DestroyDynamicActor(this.cData[slotId][this.ActorId]);

        this.cData[slotId][this.ActorId] = STREAMER_TAG_ACTOR:INVALID_ACTOR_ID;
    }

}

callback Circle.OnPlayerLeaveDynamicArea(playerid, STREAMER_TAG_AREA:areaid) {
    for new i; i < MAX_CIRCLE_OBJECT; i++ do {
        if (areaid == this.cData[i][this.AreaId]) {
            // Если игрок покинул динамическую зону пикапа
            break;
        }
    }

    return 1;
}

callback Circle.OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA:areaid) {
    for new i; i < MAX_CIRCLE_OBJECT; i++ do {
        if (areaid == this.cData[i][this.AreaId]) {
            // Если игрок зашел в динамическую зону пикапа
            break;
        }
    }

    return 1;
}
