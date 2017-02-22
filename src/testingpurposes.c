  my_dinode->mode=10;
  my_dinode->uid=1234567;
  my_dinode->gid=9876543;
  my_dinode->size=999999;
  my_dinode->a_time=2323232323;

  my_dinode->di_number[0]=0;
  my_dinode->di_number[1]=1;
  my_dinode->di_number[2]=2;
  my_dinode->di_number[3]=3;
  my_dinode->di_number[4]=4;
  my_dinode->di_number[5]=5;

  strcpy(my_dinode->names[0].name,"Platonas");
  strcpy(my_dinode->names[1].name,"Giannis");
  strcpy(my_dinode->names[2].name,"Delis");
  strcpy(my_dinode->names[3].name,"Gkomenakia");
  strcpy(my_dinode->names[4].name,"I am in love");
  strcpy(my_dinode->names[5].name,"with a stripper");

  my_dinode->isDir=true;

  my_dinode->next=20;

  metadata_add_DiNode(filename,header,my_dinode);

  strcpy(my_dinode->names[0].name,"Mairy");
  strcpy(my_dinode->names[1].name,"Eisai");
  strcpy(my_dinode->names[2].name,"Wraio");
  strcpy(my_dinode->names[3].name,"Mwraki");
  strcpy(my_dinode->names[4].name,"Pame");
  strcpy(my_dinode->names[5].name,"gia potaki?");

  metadata_add_DiNode(filename,header,my_dinode);

  my_dinode->di_number[0]=10;
  my_dinode->di_number[1]=11;
  my_dinode->di_number[2]=21;
  my_dinode->di_number[3]=31;
  my_dinode->di_number[4]=41;
  my_dinode->di_number[5]=51;

  metadata_add_DiNode(filename,header,my_dinode);

  my_dinode->di_number[0]=20;
  my_dinode->di_number[1]=21;
  my_dinode->di_number[2]=22;
  my_dinode->di_number[3]=23;
  my_dinode->di_number[4]=23;
  my_dinode->di_number[5]=25;

  metadata_add_DiNode(filename,header,my_dinode);

  strcpy(my_dinode->names[0].name,"Thelw");
  strcpy(my_dinode->names[1].name,"Na");
  strcpy(my_dinode->names[2].name,"Xorepsw");
  strcpy(my_dinode->names[3].name,"Sugxrono");
  strcpy(my_dinode->names[4].name,"thn");
  strcpy(my_dinode->names[5].name,"Tetarth");

  my_dinode->di_number[0]=40;
  my_dinode->di_number[1]=41;
  my_dinode->di_number[2]=42;
  my_dinode->di_number[3]=43;
  my_dinode->di_number[4]=43;
  my_dinode->di_number[5]=45;

  metadata_add_DiNode(filename,header,my_dinode);

  strcpy(my_dinode->names[0].name,"Lalala");
  strcpy(my_dinode->names[1].name,"Lololo");
  strcpy(my_dinode->names[2].name,"Trololo");
  strcpy(my_dinode->names[3].name,"Yoloolo");
  strcpy(my_dinode->names[4].name,"AAAAA");
  strcpy(my_dinode->names[5].name,"Bla Bla");

  my_dinode->di_number[0]=50;
  my_dinode->di_number[1]=51;
  my_dinode->di_number[2]=52;
  my_dinode->di_number[3]=53;
  my_dinode->di_number[4]=53;
  my_dinode->di_number[5]=55;

  metadata_add_DiNode(filename,header,my_dinode);

  strcpy(my_dinode->names[0].name,"Lalala");
  strcpy(my_dinode->names[1].name,"Lololo");
  strcpy(my_dinode->names[2].name,"Trololo");
  strcpy(my_dinode->names[3].name,"Yoloolo");
  strcpy(my_dinode->names[4].name,"AAAAA");
  strcpy(my_dinode->names[5].name,"Bla Bla");

  my_dinode->di_number[0]=50;
  my_dinode->di_number[1]=51;
  my_dinode->di_number[2]=52;
  my_dinode->di_number[3]=53;
  my_dinode->di_number[4]=53;
  my_dinode->di_number[5]=55;

  metadata_add_DiNode(filename,header,my_dinode);

  strcpy(my_dinode->names[0].name,"Lalala");
  strcpy(my_dinode->names[1].name,"Lololo");
  strcpy(my_dinode->names[2].name,"Trololo");
  strcpy(my_dinode->names[3].name,"Yoloolo");
  strcpy(my_dinode->names[4].name,"AAAAA");
  strcpy(my_dinode->names[5].name,"Bla Bla");

  my_dinode->di_number[0]=50;
  my_dinode->di_number[1]=51;
  my_dinode->di_number[2]=52;
  my_dinode->di_number[3]=53;
  my_dinode->di_number[4]=53;
  my_dinode->di_number[5]=55;

  metadata_add_DiNode(filename,header,my_dinode);

  strcpy(my_dinode->names[0].name,"Lalala");
  strcpy(my_dinode->names[1].name,"Lololo");
  strcpy(my_dinode->names[2].name,"Trololo");
  strcpy(my_dinode->names[3].name,"Yoloolo");
  strcpy(my_dinode->names[4].name,"AAAAA");
  strcpy(my_dinode->names[5].name,"Bla Bla");

  my_dinode->di_number[0]=50;
  my_dinode->di_number[1]=51;
  my_dinode->di_number[2]=52;
  my_dinode->di_number[3]=53;
  my_dinode->di_number[4]=53;
  my_dinode->di_number[5]=55;

  metadata_add_DiNode(filename,header,my_dinode);

  strcpy(my_dinode->names[0].name,"Lalala");
  strcpy(my_dinode->names[1].name,"Lololo");
  strcpy(my_dinode->names[2].name,"Trololo");
  strcpy(my_dinode->names[3].name,"Yoloolo");
  strcpy(my_dinode->names[4].name,"AAAAA");
  strcpy(my_dinode->names[5].name,"Bla Bla");

  my_dinode->di_number[0]=50;
  my_dinode->di_number[1]=51;
  my_dinode->di_number[2]=52;
  my_dinode->di_number[3]=53;
  my_dinode->di_number[4]=53;
  my_dinode->di_number[5]=55;

  metadata_add_DiNode(filename,header,my_dinode);
  strcpy(my_dinode->names[0].name,"Thelw");
  strcpy(my_dinode->names[1].name,"Na");
  strcpy(my_dinode->names[2].name,"Xorepsw");
  strcpy(my_dinode->names[3].name,"Sugxrono");
  strcpy(my_dinode->names[4].name,"thn");
  strcpy(my_dinode->names[5].name,"Tetarth");

  my_dinode->di_number[0]=40;
  my_dinode->di_number[1]=41;
  my_dinode->di_number[2]=42;
  my_dinode->di_number[3]=43;
  my_dinode->di_number[4]=43;
  my_dinode->di_number[5]=45;

  metadata_add_DiNode(filename,header,my_dinode);

  strcpy(my_dinode->names[0].name,"Thelw");
  strcpy(my_dinode->names[1].name,"Na");
  strcpy(my_dinode->names[2].name,"Xorepsw");
  strcpy(my_dinode->names[3].name,"Sugxrono");
  strcpy(my_dinode->names[4].name,"thn");
  strcpy(my_dinode->names[5].name,"Tetarth");

  my_dinode->di_number[0]=40;
  my_dinode->di_number[1]=41;
  my_dinode->di_number[2]=42;
  my_dinode->di_number[3]=43;
  my_dinode->di_number[4]=43;
  my_dinode->di_number[5]=45;

  metadata_add_DiNode(filename,header,my_dinode);

  strcpy(my_dinode->names[0].name,"Thelw");
  strcpy(my_dinode->names[1].name,"Na");
  strcpy(my_dinode->names[2].name,"Xorepsw");
  strcpy(my_dinode->names[3].name,"Sugxrono");
  strcpy(my_dinode->names[4].name,"thn");
  strcpy(my_dinode->names[5].name,"Tetarth");

  my_dinode->di_number[0]=60;
  my_dinode->di_number[1]=61;
  my_dinode->di_number[2]=62;
  my_dinode->di_number[3]=63;
  my_dinode->di_number[4]=63;
  my_dinode->di_number[5]=65;

  metadata_add_DiNode(filename,header,my_dinode);

  i=0;
  ret_getblock=metadata_get_block(filename,header,i,my_block);
  while(ret_getblock != -1)
  {
    for(int j=0;j<DiNodes_per_Block;j++)
    {
      printf("\n");
      printf("%d , %d , %d , %d , %d ,%d , %d , %d, %d , %d \n", my_block->table[j].mode, my_block->table[j].uid, my_block->table[j].gid, my_block->table[j].a_time, my_block->table[j].di_number[0],my_block->table[j].di_number[1],my_block->table[j].di_number[2],my_block->table[j].di_number[3],my_block->table[j].di_number[4],my_block->table[j].di_number[5]);
      printf("%s %s %s %s %s %s , %d\n",my_block->table[j].names[0].name, my_block->table[j].names[1].name, my_block->table[j].names[2].name, my_block->table[j].names[3].name, my_block->table[j].names[4].name, my_block->table[j].names[5].name, my_block->table[j].next );
      printf("\n");
    }
    i++;
    ret_getblock=metadata_get_block(filename,header,i,my_block);
  }




  /*----------------------------------------------------------------------------------------------------------------------*/

  strcpy(out_file,"picture.png");
  insert_file(header,filename,out_file);
  strcpy(out_file,"column.png");
  insert_file(header,filename,out_file);
  strcpy(out_file,"sub.png");
  insert_file(header,filename,out_file);
  strcpy(out_file,"sub.png");
  insert_file(header,filename,out_file);
  strcpy(out_file,"column.png");
  insert_file(header,filename,out_file);
  strcpy(out_file,"picture.png");
  insert_file(header,filename,out_file);

  printf("File Inserted\n");
  strcpy(out_file,"picture2.png");

  export_file(sizeof(Header),45156,out_file,filename);

  strcpy(out_file,"column2.png");

  export_file((sizeof(Header)+45156),46301,out_file,filename);

  strcpy(out_file,"sub2.png");

  export_file((sizeof(Header)+45156+46301),141119,out_file,filename);

  strcpy(out_file,"sub3.png");

  export_file((sizeof(Header)+45156+46301+141119),141119,out_file,filename);

  strcpy(out_file,"column3.png");

  export_file((sizeof(Header)+45156+46301+141119+141119),46301,out_file,filename);

  strcpy(out_file,"picture3.png");

  export_file((sizeof(Header)+45156+46301+141119+141119+46301),45156,out_file,filename);



  /*------------------------------------------------------------------------------------------------*/

  kids=0;
  strcat(my_dinode->name,".gz");

  if(fork() == 0) // The kid
  {
    uncompress_file(filename);
  }
  else
  {
    kids++;
  }

  strcat(my_dinode->name,".gz");
  if(fork() == 0) // The kid
  {
    uncompress_file(filename2);
  }
  else
  {
    kids++;
  }

  for(int k=0; k<kids; k++)
  {
    wait(&status);
    printf("Kid returned\n");
  }