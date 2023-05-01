int target = 4;
//    int nonce=0;
//    while(true)
//    {
//      string nonceStr = to_string(nonce);
//      auto now = chrono::system_clock::now();
//      time_t time =chrono::system_clock::to_time_t(now);
//      string timestr=to_string(time);
//      cout<<timestr<<endl;
//      string candidateHash=Hash(cdH+nonceStr+timestr);
//      if(validateNonce(candidateHash, target)) {cout<<candidateHash<<endl;break;}
//      nonce++;


//    }