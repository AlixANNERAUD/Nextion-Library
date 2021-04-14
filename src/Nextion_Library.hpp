///
 /// @file Nextion_Library.hpp
 /// @author Alix ANNERAUD (alix.anneraud@outlook.fr)
 /// @brief Nextion driver display.
 /// @version 0.1
 /// @date 25-05-2020
 /// 
 /// @copyright Copyright (c) 2021
 /// 

#ifndef NEXTION_LIBRARY_H_INCLUDED
#define NEXTION_LIBRARY_H_INCLUDED

#include "Arduino.h"
#include "HardwareSerial.h"
#include "FS.h"
#include "Configuration.hpp"
#include "ArduinoTrace.h"

class Nextion_Class
{
public:
    Nextion_Class();
    ~Nextion_Class();

    enum Errors
    {
        Invalid_Instruction = 0x00,
        Invalid_Component_ID = 0x02,
        Invalid_Page_ID = 0x03,
        Invalid_Picture_ID = 0x04,
        Invalid_Font_ID = 0x05,
        Invalid_File_Operation = 0x06,
        Invalid_CRC = 0x09,
        Invalid_Baud_Rate_Setting = 0x11,
        Invalid_Waveform_ID_Or_Channel = 0x12,
        Invalid_Variable_Name_Or_Attribue = 0x1A,
        Invalid_Variable_Operation = 0x1B,
        Fail_To_Assign = 0x1C,
        Fail_EEPROM_Operation = 0x1D,
        Invalid_Quantity_Of_Parameters = 0x1E,
        IO_Operation_Failed = 0x1F,
        Invalid_Escape_Character = 0x20,
        Too_Long_Variable_Name = 0x23,
        Serial_Buffer_Overflow = 0x24,
        Update_Failed = 0x25
    };

    enum Informations
    {
        Startup = 0x07,
        Instruction_Successfull = 0x01,
        Touch_Event = 0x65,
        Current_Page_Number = 0x66,
        Touch_Coordinate_Awake = 0x67,
        Touch_Coordinate_Sleep = 0x68,
        String_Data_Enclosed = 0x70,
        Numeric_Data_Enclosed = 0x71,
        Auto_Entered_Sleep_Mode = 0x86,
        Auto_Wake_From_Sleep_Mode = 0x87,
        Ready = 0x88,
        Start_Upgrade_From_SD = 0x89,
        Transparent_Data_Finished = 0xFD,
        Transparent_Data_Ready = 0xFE,
        Update_Succeed = 0x69
    };

    enum Colors
    {
        Black = 0,
        Blue = 31,
        Green = 2016,
        Yellow = 65504,
        Red = 63488,
        White = 65535
    };

    enum Alignements
    {
        Top = 0,
        Bottom = 3,
        Left = 0,
        Right = 2,
        Center = 0
    };

    enum Backgrounds
    {
        Crop_Image = 0,
        Solid_Color = 1,
        Image = 2,
        None = 3
    };

    uint8_t Page_History[5];
    uint32_t Baud_Rate;

    static Nextion_Class *Instance_Pointer;

    static void Default_Callback_Function_String_Data(const char *, uint8_t);
    static void Default_Callback_Function_Numeric_Data(uint32_t);
    static void Default_Callback_Function_Event(uint8_t);

    //

    void Purge();

    void Begin(uint32_t Baud_Rate = 921600, uint8_t RX_Pin = 16, uint8_t TX_Pin = 17);

    uint8_t Get_Receive_Pin();
    uint8_t Get_Send_Pin();

    void Set_Callback_Function_String_Data(void (*Function_Pointer)(const char *, uint8_t));
    void Set_Callback_Function_Numeric_Data(void (*Function_Pointer)(uint32_t));
    void Set_Callback_Function_Event(void (*Function_Pointer)(uint8_t));

    // Basic Geometrical Drawing
    void Draw_Pixel(uint16_t const &X_Coordinate, uint16_t const &Y_Coordinate, uint16_t const &Color);
    void Draw_Rectangle(uint16_t const &X_Coordinate, uint16_t const &Y_Coordinate, uint16_t const &Width, uint16_t const &Height, uint16_t const &Color, bool const &Hollow = false);
    void Draw_Circle(uint16_t const &X_Coordinate, uint16_t const &Y_Coordinate, uint16_t const &Radius, uint16_t const &Color, bool const &Hollow = false);
    void Draw_Fill(uint16_t const &X_Coordinate, uint16_t const &Y_Coordinate, uint16_t const &Width, uint16_t const &Height, uint16_t const &Color);
    void Draw_Line(uint16_t const &X_Start, uint16_t const &Y_Start, uint16_t const &X_End, uint16_t const &Y_End, uint16_t const &Color);

    // Advanced Drawing
    void Draw_Picture(uint16_t const &X_Coordinate, uint16_t const &Y_Coordinate, uint16_t const &Picture_ID);
    void Draw_Crop_Picture(uint16_t const &X_Coordinate, uint16_t const &Y_Coordinate, uint16_t const &Width, uint16_t const &Height, uint16_t const &Picture_ID);
    void Draw_Advanced_Crop_Picture(uint16_t const &X_Destination, uint16_t const &Y_Destination, uint16_t const &Width, uint16_t const &Height, uint16_t const &X_Coordinate, uint16_t const &Y_Coordinate, uint16_t const &Picture_ID);
    void Draw_Text(uint16_t const &X_Coordinate, uint16_t const &Y_Coordinate, uint16_t const &Width, uint16_t const &Height, uint16_t const &Font_ID, uint16_t const &Text_Color, uint16_t Backgroud, uint16_t const &Horizontal_Alignment, uint16_t const &Vertical_Alignment, uint16_t const &Background_Type, String const &Text);
    void Draw_Text(uint16_t const &X_Coordinate, uint16_t const &Y_Coordinate, uint16_t const &Width, uint16_t const &Height, uint16_t const &Font_ID, uint16_t const &Text_Color, uint16_t Backgroud, uint16_t const &Horizontal_Alignment, uint16_t const &Vertical_Alignment, uint16_t const &Background_Type, const char *Text);

    //void Print(String const& Text_To_Print);
    //void Print(const __FlashStringHelper* Text_To_Print);

    // Set Object Attributes
    void Set_Font(const __FlashStringHelper *Object_Name, uint8_t const &Font_ID);
    void Set_Background_Color(const __FlashStringHelper *Object_Name, uint16_t const &Color, int8_t Type = -1);
    void Set_Font_Color(const __FlashStringHelper *Object_Name, uint16_t const &Color, int8_t Type = -1);
    void Set_Horizontal_Alignment(const __FlashStringHelper *Object_Name, uint8_t const &Horizontal_Alignment);
    void Set_Vertical_Alignment(const __FlashStringHelper *Object_Name, uint8_t const &Set_Vertical_Alignment);
    void Set_Mask(const __FlashStringHelper *Object_Name, bool Masked);
    void Set_Wordwrap(const __FlashStringHelper *Object_Name, bool const &Wordwrap);

    void Set_Text(const __FlashStringHelper *Object_Name, char Value);
    void Set_Text(const __FlashStringHelper *Object_Name, const __FlashStringHelper *Value);
    void Set_Text(const __FlashStringHelper *Object_Name, String const &Value, uint8_t const &Insert);
    void Set_Text(String const &Object_Name, String const &Value);
    void Set_Text(const char* Object_Name, const char* Value);
    void Set_Text(const __FlashStringHelper *Object_Name, const char *Value);

    void Add_Text(const __FlashStringHelper *Component_Name, const char *Data);
    void Add_Text(const __FlashStringHelper *Object_Name, char Data);

    void Delete_Text(const __FlashStringHelper *Component_Name, uint8_t const &Quantity_To_Delete);

    void Set_Maximum_Value(const __FlashStringHelper* Object_Name, uint16_t const& Value);
    
    void Set_Minimum_Value(const __FlashStringHelper* Object_Name, uint16_t const& Value);

    void Set_Value(const __FlashStringHelper *Object_Name, uint32_t const &Value);
    void Set_Value(String const &Object_Name, uint32_t const &Value);
    void Set_Value(const char *Object_Name, uint32_t const &Value);

    void Set_Global_Value(const __FlashStringHelper *Object_Name, uint32_t const &Value);

    void Set_Channel(const __FlashStringHelper *Object_Name, uint8_t const &Channel);
    void Set_Grid_Width(const __FlashStringHelper *Object_Name, uint16_t const &Width);
    void Set_Grid_Heigh(const __FlashStringHelper *Object_Name, uint16_t const &Heigh);
    void Set_Data_Scalling(const __FlashStringHelper *Object_Name, uint16_t const &Scale);
    void Set_Picture(const __FlashStringHelper *Object_Name, uint8_t const &Picture_ID);
    void Set_Picture(String const &Object_Name, uint8_t const &Picture_ID);
    void Set_Time(const __FlashStringHelper *Object_Name, uint16_t const &Time);
    void Set_Trigger(const __FlashStringHelper *Object_Name, bool const &Enable);

    void Set_Reparse_Mode(uint8_t Mode);

    // Set System Global Variable
    void Set_Current_Page(uint8_t const &Page_ID);
    void Set_Current_Page(const __FlashStringHelper *Page_Name);
    uint8_t &Get_Current_Page();

    void Set_Brightness(uint16_t const &Brightness, bool const &Save = false);

    void Set_Display_Baud_Rate(uint32_t const &Baud_Rate, bool const &Save);

    void Set_Baud_Rate(uint32_t const& Baud_Rate);

    void Set_Font_Spacing(uint16_t const &X_Spacing, uint16_t const &Y_Spacing);

    void Set_Draw_Color(uint16_t const &Color);
    void Set_Drawing(bool const &Enable);

    void Set_Random_Generator(uint32_t const &Minimum, uint32_t const &Maximum);

    void Set_Standby_Serial_Timer(uint16_t const &Value);
    void Set_Standby_Touch_Timer(uint16_t const &Value);
    
    void Set_Serial_Wake_Up(bool Value);
    void Set_Touch_Wake_Up(bool Value);

    void Set_Wake_Up_Page(bool Value);

    void Sleep();
    void Wake_Up();

    void Set_Adress(uint16_t Adress);
    uint16_t Get_Adress();

    uint16_t Get_Free_Buffer();


    void Set_Debugging(uint8_t Level);

    void Set_Globbal_Variable(uint8_t Selected_Variable, uint32_t Value);
    void Set_Protocol(uint8_t const &Protocol_Mode);
    void Set_Wake_Up_Page(uint8_t Page_ID);

    void Start_Sending_Realtime_Coordinate();
    void Stop_Sending_Realtime_Coordinate();

    void Write(int Data);
    void Send_Raw(const __FlashStringHelper *Data);
    void Send_Raw(String const &Data);
    void Send_Raw(const char *Data);

    //Command

    void Clear(uint16_t const &Color);
    void Refresh(uint16_t const &Component_ID);
    void Refresh(const __FlashStringHelper *Object_Name);
    void Delay(uint16_t Delay_Time);
    void Click(uint16_t const &Component_ID, uint8_t const &Event_Type);
    void Click(const __FlashStringHelper *Object_Name, uint8_t const &Event_Type);
    void Click(const char *Object_Name, uint8_t const &Event_Type);
    void Start_Waveform_Refresh();
    void Stop_Waveform_Refresh();
    void Add_Value_Waveform(uint8_t const &Component_ID, uint8_t const &Channel, uint8_t *Data, uint32_t const &Quantity = 0);
    void Clear_Waveform(uint16_t const &Component_ID, uint8_t const &Channel);
    void Get(const __FlashStringHelper *Object_Name);
    void Calibrate();
    void Show(const __FlashStringHelper *Object_Name);
    void Show(String const &Object_Name);
    void Show(const char *Object_Name);
    void Hide(const __FlashStringHelper *Object_Name);
    void Hide(String const &Object_Name);
    void Hide(const char *Object_Name);
    void Disable_Touch_Event(const __FlashStringHelper *Object_Name);
    void Enable_Touch_Event(const __FlashStringHelper *Object_Name);
    void Stop_Execution();
    void Resume_Execution();
    void Refresh_Current_Page();


    void Reboot();
    uint8_t Update(File Update_File);

    void Loop();

    void Set_Semaphore_Timeout(uint32_t);
    void Get_Semaphore_Timeout(uint32_t);

protected:
    HardwareSerial Nextion_Serial;

    SemaphoreHandle_t Serial_Semaphore;

    void (*Callback_Function_String_Data)(const char *, uint8_t);
    void (*Callback_Function_Numeric_Data)(uint32_t);
    void (*Callback_Function_Event)(uint8_t);

    uint16_t Cursor_X, Cursor_Y;

    uint16_t X_Press, X_Release, Y_Press, Y_Release;

    File Temporary_File;

    uint16_t Adress;

    inline void Instruction_End()
    {
        Nextion_Serial.write(0xFF);
        Nextion_Serial.write(0xFF);
        Nextion_Serial.write(0xFF);
        xSemaphoreGive(Serial_Semaphore);
    }
    inline void Argument_Separator()
    {
        Nextion_Serial.write(',');
    }

    char Temporary_String[150];
    uint8_t Return_Code;
};

#endif