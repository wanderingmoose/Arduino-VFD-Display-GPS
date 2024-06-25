//This is setup for Noritake GU7000 VFD display
//Will justify the readings to the right. Only works with intergers, no decimals
//also displays altitude from TinyGpsPlus library Justified reading from the right.
void speed() {
  vfd.GU7000_setFontSize(2, 2, false);  // 2x2 tall & wide font
// Convert the speed value to a string
  char buffer[4];
    snprintf(buffer, sizeof(buffer), "%3d", speedint);
  // Set the cursor position to the right-justified position
  // Assuming the display width is 112 pixels and each character is 8 pixels wide
  int xPos = 135 - (strlen(buffer) * 8);
  int yPos = 0;  // Top line
  vfd.GU7000_setCursor(xPos, yPos);
  // Print the speed value to the display
  vfd.print(buffer);
   //************************

 vfd.GU7000_setFontSize(1, 1, false);  // 1x1 tall & wide font
// Convert the speed value to a string
  char buffer1[5];
    snprintf(buffer1, sizeof(buffer1), "%4d", altint);
  // Set the cursor position to the right-justified position
  // Assuming the display width is 112 pixels and each character is 8 pixels wide
  int xPos1 = 75- (strlen(buffer1) * 8);
  int yPos1 = 8;  // Bottom line
  vfd.GU7000_setCursor(xPos1, yPos1);
  // Print the speed value to the display
  vfd.print(buffer1);
}