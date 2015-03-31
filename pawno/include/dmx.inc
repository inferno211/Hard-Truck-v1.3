// Seater Vehicle V 0.2 By DmX

#if defined _Seater_Vehicles_included
#endinput
#endif

#define _Seater_Vehicles_included
#pragma library Seater_Vehicles

stock IsPlayerOnSingleVehicle(playerid) //By DmX
{
 if(IsPlayerInAnyVehicle(playerid))
 {
  new vehicleclass = GetVehicleModel(GetPlayerVehicleID(playerid));
  switch(vehicleclass)
  {
case 481:return 1;   
case 509:return 1;   
case 510:return 1;   
case 562:return 1;   
case 448:return 1;   
case 586:return 1;   
case 441:return 1;		  
case 464:return 1;   
case 465:return 1;   
case 501:return 1;   
case 564:return 1;   
case 594:return 1;   
case 553:return 1;   
case 476:return 1;		  
case 519:return 1;   
case 592:return 1;   
case 577:return 1;   
case 460:return 1;   
case 513:return 1;   
case 520:return 1;   
case 425:return 1;		  
case 553:return 1;   
case 531:return 1;   
case 568:return 1;   
case 523:return 1;   
case 532:return 1;   
case 601:return 1;   
case 485:return 1;	  
case 532:return 1;   
case 486:return 1;   
case 530:return 1;   
case 571:return 1;   
case 572:return 1;   
case 539:return 1;   
case 472:return 1;		  
case 473:return 1;   
case 484:return 1;   
case 430:return 1;   
case 453:return 1;   
case 452:return 1;   
case 493:return 1;   
case 595:return 1;		  
case 446:return 1;   
case 454:return 1;   
case 406:return 1;
  }
 }
 return 0;
}
native IsPlayerOnSingleVehicle(playerid);

stock IsPlayerOnTwoSeaterVehicle(playerid) //By DmX
{
 if(IsPlayerInAnyVehicle(playerid))
 {
  new vehicleclass = GetVehicleModel(GetPlayerVehicleID(playerid));
  switch(vehicleclass)
  {
case 401:return 1;  
case 518:return 1;  
case 527:return 1;		  
case 542:return 1;  
case 562:return 1;  
case 526:return 1;  
case 474:return 1;  
case 517:return 1;  
case 410:return 1;   
case 567:return 1;		  
case 600:return 1;  
case 436:return 1; 
case 491:return 1;
case 602:return 1;
case 429:return 1;
case 496:return 1; 
case 402:return 1;	  
case 541:return 1;  
case 589:return 1;  
case 587:return 1;  
case 565:return 1;  
case 494:return 1;  
case 502:return 1;  
case 503:return 1;		  
case 411:return 1;  
case 559:return 1;  
case 603:return 1;  
case 475:return 1;  
case 506:return 1;  
case 451:return 1;  
case 558:return 1;	  
case 477:return 1;  
case 457:return 1;  
case 537:return 1;  
case 508:return 1;  
case 438:return 1;  
case 434:return 1;  
case 545:return 1;	  
case 488:return 1;  
case 442:return 1;  
case 423:return 1;  
case 574:return 1;  
case 525:return 1;  
case 583:return 1;	  
case 548:return 1;  
case 417:return 1;  
case 488:return 1;  
case 563:return 1;  
case 447:return 1;  
case 469:return 1;  
case 499:return 1;		 
case 498:return 1;  
case 609:return 1;  
case 504:return 1;  
case 549:return 1;  
case 483:return 1;
  }
 }
 return 0;
}
native IsPlayerOnTwoSeaterVehicle(playerid);

stock IsPlayerOnFourSeaterVehicle(playerid) //By DmX
{
 if(IsPlayerInAnyVehicle(playerid))
 {
  new vehicleclass = GetVehicleModel(GetPlayerVehicleID(playerid));
  switch(vehicleclass)
  {
case 482:return 1;  
case 413:return 1; 
case 440:return 1;  
case 579:return 1;  
case 400:return 1;  
case 470:return 1;  
case 416:return 1;     
case 431:return 1;  
case 438:return 1;  
case 437:return 1;  
case 427:return 1;  
case 490:return 1;  
case 596:return 1;  
case 598:return 1; 
case 597:return 1;  
case 599:return 1;  
case 420:return 1;  
case 445:return 1;  
case 507:return 1;  
case 585:return 1;  
case 604:return 1; 
case 466:return 1;  
case 492:return 1;  
case 546:return 1;  
case 551:return 1;  
case 516:return 1;  
case 467:return 1;  
case 426:return 1;
case 547:return 1;  
case 405:return 1;  
case 580:return 1;  
case 560:return 1;  
case 550:return 1;  
case 468:return 1;  
case 540:return 1;  
case 529:return 1;  
case 421:return 1;  
case 418:return 1;  
case 404:return 1;  
case 479:return 1;  
case 458:return 1;  
case 561:return 1;
case 409:return 1;  
case 428:return 1;
  }
 }
 return 0;
}
native IsPlayerOnFourSeaterVehicle(playerid);

stock GetVehicleSeatAmmount(vehicleid) //By DmX
{
new ammount;
// 4 Seater Vehicles

switch(GetVehicleModel(vehicleid))
{
case
482,   
413,  
440,   
579,   
400,   
470,   
416,      
431,   
438,   
437,   
427,   
490,   
596,   
598,  
597,   
599,  
420,   
445,   
507,   
585,   
604,  
466,   
492,   
546,   
551,   
516,   
467,   
426,
547,   
405,   
580,   
560,   
550,   
468,   
540,   
529,   
421,   
418,   
404,   
479,   
458,   
561,
409,   
428
: return 4;

// 2 seat vehicles 
case
522,  
468,  
463,  
521,  
581,  
461,  
491	  
480,  
533,  
439,  
555,  
422,  
478,  
455, 
424,  
403,  
443,  
514,  
515,  
543,  
605,		  
408,  
552,  
478,  
456,  
554,  
536,  
575,	  
534,  
567,  
535,  
566,  
576,  
412,  
424,	  
573,  
500,  
444,  
556,  
557,  
589,  
505,	  
433,  
519,  
407,  
544,  
401,  
518,  
527,		  
542,  
562,  
526,  
474,  
517,  
410,  
567,		  
600, 
436, 
491,
602,
429,
496, 
402,	  
541,  
589,  
587,  
565,  
494,  
502,  
503,		  
411,  
559,  
603,  
475,  
506,  
451,  
558,	  
477,  
457,  
537,  
508,  
438,  
434,  
545,	  
488,  
442,  
423,  
574,  
525,  
583,	  
548,  
417,  
488,  
563,  
447,  
469,  
499,		 
498,  
609,  
504,  
549,  
483
: return 2;

// 1 seat vehicles 
case
481,   
509,   
510,   
562,   
448,   
586,   
441,		  
464,   
465,   
501,   
564,   
594,   
553,   
476,		  
519,   
592,   
577,   
460,   
513,   
520,   
425,		  
553,   
531,   
568,   
523,   
532,   
601,   
485,	  
532,   
486,   
530,   
571,   
572,   
539,   
472,		  
473,   
484,   
430,   
453,   
452,   
493,   
595,		  
446,   
454,   
406
: return 1;
}
return ammount;
}
native GetVehicleSeatAmmount(vehicleid);