void shrink() { // go get gps data using Tinygpsplus library
  speedint = int(gps.speed.kmph());
  degrees = int(gps.course.deg());
  altint = int(gps.altitude.meters());
 // satint = int(gps.satellites.value());
 }