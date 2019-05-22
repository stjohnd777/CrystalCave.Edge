//
//  ColliderComponent.hpp
//  CrystalCave.Edge
//
//  Created by Daniel St. John on 5/11/19.
//

#pragma once


 class Collider  {

 public:
     virtual void OnCollisionEnter(Collider* other) = 0;

     virtual void OnCollisionStay(Collider* other) = 0;

     virtual void OnCollisionExit(Collider* other) = 0;

 };
