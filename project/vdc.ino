//Display voltage from analog pin
void vdc() {
  vcs(); //get voltage from analog pin
  //int vlts=vlts;
  vfd.GU7000_setFontSize(1, 1, false);  // 1x1 normal font
  vfd.GU7000_setCursor(84, 8);
  vfd.print(vlts / 10, DEC);
  vfd.print(".");
  if (vlts % 100 < 10)
    vfd.print("0");
  vfd.print(vlts % 10, DEC);
  }