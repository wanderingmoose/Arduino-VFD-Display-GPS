// This custom version of delay() ensures that the gps object
// is being "fed".
//TinyGpsPlus is the library used
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read()); //Tinygpsplus library
  } while (millis() - start < ms);
}