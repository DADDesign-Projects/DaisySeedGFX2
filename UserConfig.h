//*************************************************************************
// Copyright(c) 2024 Dad Design.
//   Define here the parameters for your display and SPI interface
//*************************************************************************
#pragma once  // Prevents multiple inclusions of this header file

//-------------------------------------------------------------------------
// Screen dimensions in pixels
#define TFT_WIDTH       240       // Screen width in pixels
#define TFT_HEIGHT      320       // Screen height in pixels

//-------------------------------------------------------------------------
// Display controller type
#define TFT_CONTROLEUR_TFT  7789  // Use the ILI7789 controller
//#define TFT_CONTROLEUR_TFT  7735  // Uncomment to use the ILI7735 controller
#define TEST1 7789               // Test definition, redundant but illustrative

//-------------------------------------------------------------------------
// Color encoding
// 18-bit encoding: RGB666
// 16-bit encoding: RGB565

//-------------------------------------------------------------------------
//#define TFT_COLOR 18            // Uncomment for 18-bit color mode
#define TFT_COLOR 16              // Use 16-bit color mode (default)

//-------------------------------------------------------------------------
// SPI bus configuration
#define TFT_SPI_PORT SPI_1        // SPI port used for the display
#define TFT_SPI_MODE Mode3        // SPI mode (Mode 3: CPOL = 1, CPHA = 1)
#define TFT_SPI_BaudPrescaler PS_8 // SPI baud rate prescaler

// GPIO configuration for SPI pins
#define TFT_MOSI D10              // SPI MOSI (Master Out, Slave In) pin
#define TFT_SCLK D8               // SPI clock (SCLK) pin
#define TFT_DC   D21              // Data/Command control pin
#define TFT_RST  D20              // Reset pin for the display

//-------------------------------------------------------------------------
// Define the block size used for partial screen updates
//   -> Only blocks that have been modified are sent to the display
// Note:
// - TFT_WIDTH must be evenly divisible by BLOC_WIDTH
// - TFT_HEIGHT must be evenly divisible by BLOC_HEIGHT
// Example: For a 240x320 screen, a block size of 24x32 is valid
#define NB_BLOC_WIDTH   10               // Number of blocks horizontally
#define NB_BLOC_HEIGHT  10               // Number of blocks vertically
#define NB_BLOCS        NB_BLOC_WIDTH * NB_BLOC_HEIGHT // Total number of blocks
#define BLOC_WIDTH      TFT_WIDTH / NB_BLOC_WIDTH      // Width of each block in pixels
#define BLOC_HEIGHT     TFT_HEIGHT / NB_BLOC_HEIGHT    // Height of each block in pixels

//-------------------------------------------------------------------------
// FIFO size for SPI block transmission via DMA
// Note: The number is limited due to FIFO being placed in SRAM D1, 
// which may also be used by other processes
#define SIZE_FIFO 5  // Number of blocks in the FIFO buffer
