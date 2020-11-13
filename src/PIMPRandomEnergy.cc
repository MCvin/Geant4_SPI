// Generate Random Energy

#include "PIMPRandomEnergy.hh"
#include "globals.hh"
#include "Randomize.hh"

PIMPRandomEnergy::PIMPRandomEnergy()
{;}

PIMPRandomEnergy::~PIMPRandomEnergy()
{;}

  
// G4double PIMPRandomEnergy::GenerateRandomEnergy(G4int* Regions, 
//                                                 G4double Boundaries[], 
//                                                 G4double Indecies[],
//                                                 G4double Norms[]) 
// {
//   G4double Integration[] = {0., 0., 0., 0., 0., 0.};
//   G4double TotalIntegration = 0. ;

//   for (int incr=0; incr < *Regions ; ++incr)
//     {
//       Integration[incr] = Norms[incr] * ( (pow(Boundaries[incr+1],Indecies[incr]+1.0)
// 					   /(Indecies[incr]+1.0)) -
// 					  (pow(Boundaries[incr],Indecies[incr]+1.0)
// 					   /(Indecies[incr]+1.0)) ) ;
//       TotalIntegration = TotalIntegration + Integration[incr] ;
//     }

//   G4double Random = G4UniformRand() ;
//   Random = Random * TotalIntegration ;
  
//   TotalIntegration = 0. ;
//   for (incr=0; incr < *Regions; ++incr)
//     {
//       TotalIntegration = TotalIntegration + Integration[incr] ; 
//       if (Random <= TotalIntegration )
// 	{
// 	  for (int subincr = incr - 1; subincr >= 0 ; --subincr)
// 	    {
// 	      Random = Random - Integration[subincr] ;
// 	    }
// 	  Random = ((Random/Norms[incr]) + 
// 		    pow(Boundaries[incr],Indecies[incr]+1.0)/(Indecies[incr]+1.0))
// 	    * (Indecies[incr]+1.0) ;
// 	  Random = pow( Random, (1.0/(Indecies[incr]+1.0)) ) ;
	  
// 	  incr = (*Regions)+1 ;
// 	}
//     }

//   return Random ;

// };



// G4double PIMPRandomEnergy::GenerateRandomEnergy(G4int* NumOfLines, 
// 						G4double Energy[], 
// 						G4double Probability[]) 
// {
//   G4double Weight = 0; 
//   for(int i = 0; i < *NumOfLines ; ++i)
//     {
//       Weight = Weight + Probability[i] ;
//     }
    
//   G4double Random = G4UniformRand() ;
//   G4double Prob = 0 ;

//   // G4cout << "Random:  " << Random << G4endl ; 
//   // G4cout << "NumOfLines: " << *NumOfLines << G4endl ; 
//   for(int incr = 0; incr < *NumOfLines ; ++incr)
//     {
//       // G4cout << incr << G4endl ; 
//       Prob = Prob + Probability[incr] ;
//       // G4cout << Prob << " " <<  Probability[incr] << G4endl ; 
//       if(Random <= Prob)
// 	{
// 	  Random = Energy[incr];
// 	  // G4cout << "--> " << Random << G4endl ;
// 	  return Random;
// 	}
//     }

//   return Random;

// };

G4double PIMPRandomEnergy::GenerateRandomEnergy(G4double Alpha,
						G4double Beta,
						G4double Ebreak,
						G4double LowEnergyTotal,
						G4double HighEnergyTotal) 
{
  // G4cout << Alpha << " " << Beta << " " << Ebreak << " " << LowEnergyTotal << " " << HighEnergyTotal << G4endl ;

  G4double TotalIntegration = LowEnergyTotal + HighEnergyTotal ;
  Random = G4UniformRand() ;
  // cout << "Random Number: " << Random << endl ;
  Random = Random * TotalIntegration ;
  if (Random >= LowEnergyTotal)
    {
      // cout << Alpha << " " << Beta << " " << Ebreak << " " << LowEnergyTotal << " " << HighEnergyTotal << endl ;
      Random = Random - LowEnergyTotal ;
      /*
      cout << "Rand: " << Random << endl ;
      G4double Factor = pow(100,Alpha) *
	pow((Alpha-Beta),(Alpha-Beta)) *
	pow(Ebreak,(Alpha-Beta)) *
	pow(2.71828183,(Beta-Alpha)) *
	(1/(Beta+1)) ;
      cout << Factor << "  Factor" << endl ;
      G4double Break = (Alpha-Beta) * Ebreak ;
      cout << Break << "  Break" << endl ;
      Random = 0.001 * (pow( ((Random + Factor*pow(Break,(Beta+1))) / Factor), 
	 		     (1/(Beta+1)) )) ;
      */
//        G4cout << "Rand: " << Random << G4endl ;
      G4double Factor = (100./(Beta+1)) *
	std::pow( ( (Alpha-Beta)*Ebreak/100. ) , (Alpha-Beta) ) *
	std::pow(2.71828183,(Beta-Alpha)) ;
//        G4cout << Factor << "  Factor" << G4endl ;
      G4double Break = (Alpha-Beta) * Ebreak ;
//        G4cout << Break << "  Break" << G4endl ;
      Random = 0.1 * std::pow( ((Random/Factor) + std::pow((Break/100),(Beta+1))),(1/(Beta+1))) ;
 //       G4cout << "E out: " << Random << G4endl ;
    }
  else
    {
      // The idea is to integrate up, using Bode's Law, in increments until the
      // 5kev segments total greater than "Random". Then to go back and find out which
      // kev bin "Random" lies in and interpolate linearly.

      G4double Break = (Alpha-Beta) * Ebreak ;
      G4double Ene = 20.0 ; // lower limit is 12 keV      
      G4double IntegrateUp = 0. ;
      G4double UpToSegment ;

//        G4cout << "Before first while : " << IntegrateUp << " " << Random << G4endl ;
      while( IntegrateUp < Random )
	{ 
	  G4double KevIntegration[5] = {0., 0., 0., 0., 0.}; 
	  for (int i = 0 ; i < 5 ; i++)
	    {
	      KevIntegration[i] = ( std::pow((Ene/100.),Alpha) * 
				    std::pow(2.71828183, (-1.0*Ene/Ebreak)) ) ;
	      //G4cout << "KevIntergration, i: " << KevIntegration[i] << G4endl ;
	    //    ( pow(((Ene+1.0)/100.),Alpha) * 
// 	       	      pow(2.71828183, (-1.0*(Ene+1.0)/Ebreak)) ) ) / 2.0 ;
	      Ene = Ene + 1.0 ;
	    }
	  Ene = Ene - 1.0 ;
	  G4double TotalSegment = 1.0 * ( (14./45.)*KevIntegration[0] +
					  (64./45.)*KevIntegration[1] +
					  (24./45.)*KevIntegration[2] +
					  (64./45.)*KevIntegration[3] +
					  (14./45.)*KevIntegration[4] );
	  UpToSegment = IntegrateUp ;
	  IntegrateUp = IntegrateUp + TotalSegment ; 
// 	    G4cout << "Random:: " << Random 
//  	      << " IntegrateUp: " << IntegrateUp 
//  	      << " Energy: " << Ene << G4endl ;
	}
      // Random is inside this segment      
      Ene = Ene - 4.0 ;       
      G4double UpToKeV ;
//        G4cout << "Before second while : " << IntegrateUp << " " << Random << G4endl ;
       while( UpToSegment < Random )
	{     
	  UpToKeV = UpToSegment ;
	  UpToSegment = UpToSegment + ( ( std::pow((Ene/100.),Alpha) * 
					  std::pow(2.71828183, (-1.0*Ene/Ebreak)) ) +
					( std::pow(((Ene+1.0)/100.),Alpha) * 
					  std::pow(2.71828183, (-1.0*(Ene+1.0)/Ebreak)) ) ) / 2.0 ; 
	  // cout << "Random:: " << Random 
	  //      << " UpToSegment: " << UpToSegment 
	  //    << " Energy: " << Ene << endl ;
	  Ene = Ene + 1.0 ;
	}

      Ene = Ene - 1.0 ;
      // Find the parameters for the linear interpolation
      G4double Slope = ( std::pow(((Ene+1.0)/100.),Alpha) * 
			 std::pow(2.71828183, (-1.0*Ene/Ebreak)) -
			 std::pow(((Ene)/100.),Alpha) * 
			 std::pow(2.71828183, (-1.0*(Ene+1.0)/Ebreak)) )/(1.0) ;
      G4double Intercept = ( std::pow((Ene/100.),Alpha) * 
			     std::pow(2.71828183, (-1.0*Ene/Ebreak)) ) - (Slope * Ene) ;
      Random = Random - UpToKeV ;

//        G4cout << "Random:: " << Random 
//         	   << " Slope: " << Slope 
//         	   << " Intercept: " << Intercept << G4endl ; 
      // ---- Now interpolate ----
      G4double A = Slope/2.0 ;
      G4double B = Slope*Ene + Intercept ;
      G4double C = -1.0 * Random ;
      Random = (((-1.0*B + std::pow((std::pow(B,2)-4*A*C),0.5))/(2.0*A)) + Ene)* 0.001 ;
    }
  // cout << "Returns ... " << Random << endl ; 
  return Random ;

//   G4double TotalIntegration = LowEnergyTotal + HighEnergyTotal ;
//   G4double Random = G4UniformRand() ;
//   // G4cout << "Random Number: " << Random << G4endl ;
//   Random = Random * TotalIntegration ;
//   if (Random >= LowEnergyTotal)
//     {
//       Random = Random - LowEnergyTotal ;
//       // G4cout << "Rand: " << Random << G4endl ;
//       G4double Factor = pow(100,Alpha) *
// 	pow((Alpha-Beta),(Alpha-Beta)) *
// 	pow(Ebreak,(Alpha-Beta)) *
// 	pow(2.71828183,(Beta-Alpha)) *
// 	(1/(Beta+1)) ;
//       // G4cout << Factor << "  Factor" << G4endl ;
//       G4double Break = (Alpha-Beta) * Ebreak ;
//       //  G4cout << Break << "  Break" << G4endl ;
//       Random = 0.001 * (pow( ((Random + Factor*pow(Break,(Beta+1))) / Factor), 
// 			     (1/(Beta+1)) )) ;
//       //      G4cout << "E out: " << Random << G4endl ;
//     }
//   else
//     {
//       // The idea is to integrate up, using Bode's Law, in increments until the
//       // 5kev segments total greater than "Random". Then to go back and find out which
//       // kev bin "Random" lies in and interpolate linearly.

//       G4double Break = (Alpha-Beta) * Ebreak ;
//       G4double Ene = 20.0 ; // lower limit is 20 keV      
//       G4double IntegrateUp = 0. ;
//       G4double UpToSegment ;

//       //       G4cout << "Before first while : " << IntegrateUp << " " << Random << G4endl ;
//       while( IntegrateUp < Random )
// 	{ 
// 	  G4double KevIntegration[5] = {0., 0., 0., 0., 0.}; 
// 	  for (int i = 0 ; i < 5 ; i++)
// 	    {
// 	      KevIntegration[i] = ( pow((Ene/100.),Alpha) * 
// 				    pow(2.71828183, (-1.0*Ene/Ebreak)) ) ;
// 	      //	      G4cout << "KevIntergration, i: " << KevIntegration[i] << G4endl ;
// 	      // ( pow(((Ene+1.0)/100.),Alpha) * 
// 	      // 	      pow(2.71828183, (-1.0*(Ene+1.0)/Ebreak)) ) ) / 2.0 ;
// 	      Ene = Ene + 1.0 ;
// 	    }
// 	  Ene = Ene - 1.0 ;
// 	  G4double TotalSegment = 1.0 * ( (14./45.)*KevIntegration[0] +
// 					  (64./45.)*KevIntegration[1] +
// 					  (24./45.)*KevIntegration[2] +
// 					  (64./45.)*KevIntegration[3] +
// 					  (14./45.)*KevIntegration[4] );
// 	  UpToSegment = IntegrateUp ;
// 	  IntegrateUp = IntegrateUp + TotalSegment ; 
// 	  //	  G4cout << "Random:: " << Random 
// 	  //	    << " IntegrateUp: " << IntegrateUp 
// 	  //	    << " Energy: " << Ene << G4endl ;
// 	}
//       // Random is inside this segment      
//       Ene = Ene - 4.0 ;       
//       G4double UpToKeV ;
//       while( UpToSegment < Random )
// 	{     
// 	  UpToKeV = UpToSegment ;
// 	  UpToSegment = UpToSegment + ( ( pow((Ene/100.),Alpha) * 
// 					  pow(2.71828183, (-1.0*Ene/Ebreak)) ) +
// 					( pow(((Ene+1.0)/100.),Alpha) * 
// 					  pow(2.71828183, (-1.0*(Ene+1.0)/Ebreak)) ) ) / 2.0 ; 
// 	  // cout << "Random:: " << Random 
// 	  //     << " UpToSegment: " << UpToSegment 
// 	  //   << " Energy: " << Ene << endl ;
// 	  Ene = Ene + 1.0 ;
// 	}

//       Ene = Ene - 1.0 ;
//       // Find the parameters for the linear interpolation
//       G4double Slope = ( pow(((Ene+1.0)/100.),Alpha) * 
// 			 pow(2.71828183, (-1.0*Ene/Ebreak)) -
// 			 pow(((Ene)/100.),Alpha) * 
// 			 pow(2.71828183, (-1.0*(Ene+1.0)/Ebreak)) )/(1.0) ;
//       G4double Intercept = ( pow((Ene/100.),Alpha) * 
// 			     pow(2.71828183, (-1.0*Ene/Ebreak)) ) - (Slope * Ene) ;
//       Random = Random - UpToKeV ;

//       //       G4cout << "Random:: " << Random 
//       //       	   << " Slope: " << Slope 
//       //       	   << " Intercept: " << Intercept <<G4endl ; 
//       // ---- Now interpolate ----
//       G4double A = Slope/2.0 ;
//       G4double B = Slope*Ene + Intercept ;
//       G4double C = -1.0 * Random ;
//       Random = (((-1.0*B + pow((pow(B,2)-4*A*C),0.5))/(2.0*A)) + Ene)* 0.001 ;
//     }
//   //  G4cout << "Returns ... " << Random << G4endl ; 
//   return Random ;
      
}






