#include "project.h"
#include <stdio.h>
#include "GUI.h"
#include "pervasive_eink_hardware_driver.h"
#include "cy_eink_library.h"
#include "LCDConf.h"

#include "BLEFindMe.h"

/* Frame buffers */
uint8 imageBufferCache[CY_EINK_FRAME_SIZE] = {0};
uint8 imageBuffer[CY_EINK_FRAME_SIZE] = {0};

void UpdateDisplay(cy_eink_update_t updateMethod, bool powerCycle)
{
    /* Copy the EmWin display buffer to imageBuffer*/
    LCD_CopyDisplayBuffer(imageBuffer, CY_EINK_FRAME_SIZE);

    /* Update the EInk display */
    Cy_EINK_ShowFrame(imageBufferCache, imageBuffer, updateMethod, powerCycle);

    /* Copy the EmWin display buffer to the imageBuffer cache*/
    LCD_CopyDisplayBuffer(imageBufferCache, CY_EINK_FRAME_SIZE);
    
}

void ShowStartupScreen(void)
{
    int i=0,j=0;
    /* Set foreground and background color and font size */
    GUI_SetFont(GUI_FONT_24B_1);
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();

    GUI_DrawCircle(55, 55, 50);
    GUI_SetPenSize(10);
    GUI_DrawCircle(35, 45, 10);
    GUI_DrawCircle(75, 45, 10);
    
    GUI_FillRoundedRect(66, 66, 55, 55, 5);
    
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("Vasylkiv",190, 10);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("Maksym", 190, 30);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("FEI-33", 190, 50);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("12.04.2024", 190, 70);
    GUI_DispStringAt("Lab 10 FindMeAlert", 100, 90);
    
    UpdateDisplay(CY_EINK_FULL_4STAGE, true);
}

int main(void)
{
    //uint8 pageNumber = 0;
    BleFindMe_Init();
    __enable_irq(); /* Enable global interrupts. */

    /* Initialize emWin Graphics */
    GUI_Init();
    
    /* Start the eInk display interface and turn on the display power */
    Cy_EINK_Start(20);
    Cy_EINK_Power(1);
    
         /* Show the startup screen */
    ShowStartupScreen();
    
    
    for(;;)
    {
       BleFindMe_Process();
    }
}

/* [] END OF FILE */
