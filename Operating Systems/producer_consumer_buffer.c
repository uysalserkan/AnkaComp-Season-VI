while (true) {
       /* Produce an item */
        while ( ((in + 1) % BUFFER SIZE)  == out)
	     ;   /* do nothing -- no free buffers */
	    buffer[in] = item;
	    in = (in + 1) % BUFFER SIZE;
     }

while (true) {
          while (in == out)
                 ; // do nothing -- nothing to consume

	     // remove an item from the buffer
	     item = buffer[out];
	     out = (out + 1) % BUFFER SIZE;
	return item;
     }
