void autoDrive()
{
  currentMillis = millis();

  Serial.println("forwardDistance1 = " + String(dist1) + "\nleftDistance2 = " + String(dist2) + "\nrightDistance3 = " + String(dist3));

  if (state_a && !lookedLeft && !lookedRight)
  {
    dist1 = obstacle();
  }

  if (dist1 < thresholdDist) //if read distance is less than the thresholdDist. Set a flag here that becomes true if this condition is met
  {
    condition_a = true;

    if (state_a && !lookLeft)
    {
      servo.write(lookLeft);
      Serial.println("LOOKED LEFFFFFFFFFFFFFT O");
      lookedLeft = true;
    }
    lookedRight = false;
  }

  if (dist1 > thresholdDist)
  {
    condition_a = false;
    lookedLeft = false;
    lookedRight = false;
  }


  if (currentMillis - prevMillis < firstInterval) // remains true from t0 ---> t1
  {
    state_a = true;
    state_b = false;
    state_c = false;
    state_d = false;
    state_e = false;
    state_f = false;
    state_g = false;
  }

  if (currentMillis - prevMillis > firstInterval && currentMillis - prevMillis < secondInterval) // remains true from t1 ---> t2
  {
    state_a = false;
    state_b = true;
    state_c = false;
    state_d = false;
    state_e = false;
    state_f = false;
    state_g = false;
  }

  if (currentMillis - prevMillis > secondInterval && currentMillis - prevMillis < thirdInterval) // remains true for t2 ---> t3
  {
    state_a = false;
    state_b = false;
    state_c = true;
    state_d = false;
    state_e = false;
    state_f = false;
    state_g = false;
  }

  if (currentMillis - prevMillis > thirdInterval && currentMillis - prevMillis < fourthInterval) // remains true for t3 ---> t4
  {
    state_a = false;
    state_b = false;
    state_c = false;
    state_d = true;
    state_e = false;
    state_f = false;
    state_g = false;
  }

  if (currentMillis - prevMillis > fourthInterval && currentMillis - prevMillis < fifthInterval)
  {
    state_a = false;
    state_b = false;
    state_c = false;
    state_d = false;
    state_e = true;
    state_f = false;
    state_g = false;
  }

  if (currentMillis - prevMillis > fifthInterval && currentMillis - prevMillis < sixthInterval)
  {
    state_a = false;
    state_b = false;
    state_f = true;
    state_g = false;
    //    prevMillis = currentMillis;
  }

  if (currentMillis - prevMillis > sixthInterval && currentMillis - prevMillis < seventhInterval)
  {
    state_a = false;
    state_b = false;
    state_c = false;
    state_d = false;
    state_e = false;
    state_f = false;
    state_g = true;
    //    prevMillis = currentMillis;
  }

  if (currentMillis - prevMillis > seventhInterval)
  {
    state_a = false;
    state_b = false;
    state_c = false;
    state_d = false;
    state_e = false;
    state_f = false;
    state_g = false;
    //    prevMillis = currentMillis;
  }

  if (!state_a && !state_b && !state_c && !state_d && !state_e && !state_f && !state_g && !lookingAhead) //  if the first distance is > than the thresholdDist
  {
    //Test other flags  and keep moving forward_iterator

    servo.write(lookAhead);
    front();
    //    prevMillis = currentMillis;  ///-----------------------------not quite sure if this should be here

    //reset all the states to DEFAULT where ROBOT is movingForward and lookingAhead
    condition_a = false;
    condition_b = false;
    condition_c = false;
    state_a = false;
    state_b = false;
    state_c = false;
    state_d = false;
    state_e = false;
    state_f = false;
    state_g = false;
    lookingAhead = true;
    lookedLeft = false;
    lookedRight = false;
    movingForward = true;
    movingBackward = false;
    movingLeft = false;
    movingRight = false;

    dist1 = 0.0;
    dist2 = 0.0;
    dist3 = 0.0;

    Serial.println("NOTHING DEY SHELELE");
  }

  if (state_b && condition_a && lookedLeft && !lookedRight)
  {
    dist2 = obstacle();
    //for debugging
    Serial.println("STOPPED HERE TO READ LEFT DISTANCE........2");
    //    servo.write(lookLeft);
    lookedLeft = true;
    lookedRight = false;
  }

  if (dist2 < thresholdDist)
  {

    condition_b = true;
    condition_a = true;
    lookedLeft = true;
    lookedRight = false;
  }

  if (dist2 > thresholdDist)
  {
    condition_b = false;
    condition_a = true;
    lookedLeft = true;
    lookedRight = false;
  }

  if (state_c && lookedLeft && !lookedRight)
  {
    servo.write(lookRight);

    //for debugging
    Serial.println("LOOKED RIGHT......3");
    lookedRight = true;
    lookedLeft = true;
    lookingAhead = false;
  }

  if (state_d && condition_b && lookedLeft && lookedRight)
  {
    dist3 = obstacle();

    //for debugging
    Serial.println("STOPPED HERE TO READ RIGHT DISTANCE.........4");
  }

  if  (dist3 < thresholdDist)
  {
    condition_c = true;
    lookedRight = true;
    lookedLeft = true;
    lookingAhead = false;
  }

  if (dist3 > thresholdDist)
  {
    condition_c = false;
    lookedRight = true;
    lookedLeft = true;
    lookingAhead = false;
  }

  if (state_e && !lookingAhead)
  {
    servo.write(lookAhead);
    lookingAhead = true;
    lookedRight = true;
    lookedLeft = true;

    //for debugging
    Serial.println("LOOKED AHEAD HERE...........5");
  }

  if (state_g) //means it has completed it's  cycle
  {
    prevMillis = currentMillis;
    lookedLeft = true;
    lookedRight = true;

    //for debugging
    Serial.println("COMPLETE CYCLE!..................6");
  }

  if (condition_a) //means forward distance is less than threshold
  {
    //check other  states (a-f)
    //set flags for movingLeft, movingRight, movingForward, and movingBackward

    if (condition_b && state_f) //if the left distance is less than the threshold and it has completed it's scan cycle
    {
      if (condition_c) //
      {
        movingBackward = true; // move backward
        movingForward = false;
        movingLeft = false;
        movingRight = false;
      }
      else if (condition_c == false) // if the right distance is greater than the threshold, turn right
      {
        movingRight = true;  // move right
        movingBackward = false; // move backward
        movingForward = false;
        movingLeft = false;
      }
    }

    if (condition_b == false && state_f) // if the left distance is greater than the threshold and it has completed it's cycle
    {
      //turn left
      movingLeft = true;
      movingBackward = false;
      movingForward = false;
      movingRight = false;

      //for debugging
      Serial.println("MOVING LEFT HERE");

    }

    if (condition_c)
    {
      if (condition_b && state_f)
      {
        //move backwards here
        movingLeft = false;
        movingBackward = true;
        movingForward = false;
        movingRight = false;
        //for debugging
        Serial.println("MOVING BACKWARD HERE......");
      }

    }

    if (condition_c == false && state_f)   // if the right distance is greater than the threshold, turn right
    {
      //for debugging
      Serial.println("MOVING RIGHT HERE............");
      movingLeft = false;
      movingBackward = false;
      movingForward = false;
      movingRight = true;
    }
  }


  //if (condition_b) // means left distance is less than threshold
  //{
  //check other states (a-f)
  //set flags for movingLeft, movingRight, movingForward, and movingBackward
  //if (condition_c &&)
  //}

  //if (condition_c) // means right distance is less than threshold
  //{
  //check other states (a-f)
  //set flags for movingLeft, movingRight, movingForward, and movingBackward
  //}



  if (movingForward)
  {
    //move forward till a specific time. How do I do this???????
  }

  if (movingBackward)
  {
    //move backward till a specific time. how do I do this????????????????
    servo.write(lookAhead);
  }

  if (movingLeft)
  {
    //move left till a specific time. how do I do this????????????????????
  }

  if (movingRight)
  {
    //move right till a specific time. How do I do this???????????????
  }

  if (movingForward && state_f)
  {
    //move forward till a specific time. How do I do this???????
    servo.write(lookAhead);
  }

  if (movingBackward && state_f)
  {
    //move backward till a specific time. how do I do this????????????????
    servo.write(lookAhead);
  }

  if (movingLeft && state_f)
  {
    //move left till a specific time. how do I do this????????????????????
    servo.write(lookAhead);
  }

  if (movingRight && state_f)
  {
    //move right till a specific time. How do I do this???????????????
    servo.write(lookAhead);
  }


  if (state_a || state_b || state_c || state_d || state_e || state_f || state_g && dist1 > thresholdDist)
  {
    //do nothing
  }

  else
  {
    //false

    //------I'M CURRENTLY HERE OOOH. I'd like to test condition_c but need to verify the flow
    //WAIT AND DO NOTHING
    //for debugging
    Serial.println("WAITING HERE FOR THE OTHER CONDITIONS..........");
  }

}//END Autodrive