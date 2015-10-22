// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME mydict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "DTCalibrationMap.h"
#include "DTCut.h"
#include "DTDetId.h"
#include "DTHistoPlotter.h"
#include "DTHitObject.h"
#include "DTMuObject.h"
#include "DTSegmentObject.h"
#include "FEDNtupleReader.h"
#include "FEDNumbering.h"
#include "Histograms.h"
#include "SimTreeReader.h"
#include "TTreeReader.h"
#include "Utils.h"

// Header files passed via #pragma extra_include

namespace Utils {
   namespace ROOT {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *Utils_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("Utils", 0 /*version*/, "Utils.h", 17,
                     ::ROOT::DefineBehavior((void*)0,(void*)0),
                     &Utils_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *Utils_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}

namespace ROOT {
   static void *new_DTHitObject(void *p = 0);
   static void *newArray_DTHitObject(Long_t size, void *p);
   static void delete_DTHitObject(void *p);
   static void deleteArray_DTHitObject(void *p);
   static void destruct_DTHitObject(void *p);
   static void streamer_DTHitObject(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::DTHitObject*)
   {
      ::DTHitObject *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::DTHitObject >(0);
      static ::ROOT::TGenericClassInfo 
         instance("DTHitObject", ::DTHitObject::Class_Version(), "../../src/DTHitObject.h", 18,
                  typeid(::DTHitObject), DefineBehavior(ptr, ptr),
                  &::DTHitObject::Dictionary, isa_proxy, 16,
                  sizeof(::DTHitObject) );
      instance.SetNew(&new_DTHitObject);
      instance.SetNewArray(&newArray_DTHitObject);
      instance.SetDelete(&delete_DTHitObject);
      instance.SetDeleteArray(&deleteArray_DTHitObject);
      instance.SetDestructor(&destruct_DTHitObject);
      instance.SetStreamerFunc(&streamer_DTHitObject);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::DTHitObject*)
   {
      return GenerateInitInstanceLocal((::DTHitObject*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::DTHitObject*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_DTMuObject(void *p = 0);
   static void *newArray_DTMuObject(Long_t size, void *p);
   static void delete_DTMuObject(void *p);
   static void deleteArray_DTMuObject(void *p);
   static void destruct_DTMuObject(void *p);
   static void streamer_DTMuObject(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::DTMuObject*)
   {
      ::DTMuObject *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::DTMuObject >(0);
      static ::ROOT::TGenericClassInfo 
         instance("DTMuObject", ::DTMuObject::Class_Version(), "../../src/DTMuObject.h", 17,
                  typeid(::DTMuObject), DefineBehavior(ptr, ptr),
                  &::DTMuObject::Dictionary, isa_proxy, 16,
                  sizeof(::DTMuObject) );
      instance.SetNew(&new_DTMuObject);
      instance.SetNewArray(&newArray_DTMuObject);
      instance.SetDelete(&delete_DTMuObject);
      instance.SetDeleteArray(&deleteArray_DTMuObject);
      instance.SetDestructor(&destruct_DTMuObject);
      instance.SetStreamerFunc(&streamer_DTMuObject);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::DTMuObject*)
   {
      return GenerateInitInstanceLocal((::DTMuObject*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::DTMuObject*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_DTSegmentObject(void *p = 0);
   static void *newArray_DTSegmentObject(Long_t size, void *p);
   static void delete_DTSegmentObject(void *p);
   static void deleteArray_DTSegmentObject(void *p);
   static void destruct_DTSegmentObject(void *p);
   static void streamer_DTSegmentObject(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::DTSegmentObject*)
   {
      ::DTSegmentObject *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::DTSegmentObject >(0);
      static ::ROOT::TGenericClassInfo 
         instance("DTSegmentObject", ::DTSegmentObject::Class_Version(), "../../src/DTSegmentObject.h", 21,
                  typeid(::DTSegmentObject), DefineBehavior(ptr, ptr),
                  &::DTSegmentObject::Dictionary, isa_proxy, 16,
                  sizeof(::DTSegmentObject) );
      instance.SetNew(&new_DTSegmentObject);
      instance.SetNewArray(&newArray_DTSegmentObject);
      instance.SetDelete(&delete_DTSegmentObject);
      instance.SetDeleteArray(&deleteArray_DTSegmentObject);
      instance.SetDestructor(&destruct_DTSegmentObject);
      instance.SetStreamerFunc(&streamer_DTSegmentObject);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::DTSegmentObject*)
   {
      return GenerateInitInstanceLocal((::DTSegmentObject*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::DTSegmentObject*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *DTDetId_Dictionary();
   static void DTDetId_TClassManip(TClass*);
   static void *new_DTDetId(void *p = 0);
   static void *newArray_DTDetId(Long_t size, void *p);
   static void delete_DTDetId(void *p);
   static void deleteArray_DTDetId(void *p);
   static void destruct_DTDetId(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::DTDetId*)
   {
      ::DTDetId *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::DTDetId));
      static ::ROOT::TGenericClassInfo 
         instance("DTDetId", "DTDetId.h", 14,
                  typeid(::DTDetId), DefineBehavior(ptr, ptr),
                  &DTDetId_Dictionary, isa_proxy, 0,
                  sizeof(::DTDetId) );
      instance.SetNew(&new_DTDetId);
      instance.SetNewArray(&newArray_DTDetId);
      instance.SetDelete(&delete_DTDetId);
      instance.SetDeleteArray(&deleteArray_DTDetId);
      instance.SetDestructor(&destruct_DTDetId);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::DTDetId*)
   {
      return GenerateInitInstanceLocal((::DTDetId*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::DTDetId*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *DTDetId_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::DTDetId*)0x0)->GetClass();
      DTDetId_TClassManip(theClass);
   return theClass;
   }

   static void DTDetId_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *HRes1DHits_Dictionary();
   static void HRes1DHits_TClassManip(TClass*);
   static void delete_HRes1DHits(void *p);
   static void deleteArray_HRes1DHits(void *p);
   static void destruct_HRes1DHits(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HRes1DHits*)
   {
      ::HRes1DHits *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::HRes1DHits));
      static ::ROOT::TGenericClassInfo 
         instance("HRes1DHits", "Histograms.h", 14,
                  typeid(::HRes1DHits), DefineBehavior(ptr, ptr),
                  &HRes1DHits_Dictionary, isa_proxy, 0,
                  sizeof(::HRes1DHits) );
      instance.SetDelete(&delete_HRes1DHits);
      instance.SetDeleteArray(&deleteArray_HRes1DHits);
      instance.SetDestructor(&destruct_HRes1DHits);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HRes1DHits*)
   {
      return GenerateInitInstanceLocal((::HRes1DHits*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::HRes1DHits*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *HRes1DHits_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::HRes1DHits*)0x0)->GetClass();
      HRes1DHits_TClassManip(theClass);
   return theClass;
   }

   static void HRes1DHits_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *HSegment_Dictionary();
   static void HSegment_TClassManip(TClass*);
   static void delete_HSegment(void *p);
   static void deleteArray_HSegment(void *p);
   static void destruct_HSegment(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HSegment*)
   {
      ::HSegment *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::HSegment));
      static ::ROOT::TGenericClassInfo 
         instance("HSegment", "Histograms.h", 196,
                  typeid(::HSegment), DefineBehavior(ptr, ptr),
                  &HSegment_Dictionary, isa_proxy, 0,
                  sizeof(::HSegment) );
      instance.SetDelete(&delete_HSegment);
      instance.SetDeleteArray(&deleteArray_HSegment);
      instance.SetDestructor(&destruct_HSegment);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HSegment*)
   {
      return GenerateInitInstanceLocal((::HSegment*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::HSegment*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *HSegment_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::HSegment*)0x0)->GetClass();
      HSegment_TClassManip(theClass);
   return theClass;
   }

   static void HSegment_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *DTHistoPlotter_Dictionary();
   static void DTHistoPlotter_TClassManip(TClass*);
   static void *new_DTHistoPlotter(void *p = 0);
   static void *newArray_DTHistoPlotter(Long_t size, void *p);
   static void delete_DTHistoPlotter(void *p);
   static void deleteArray_DTHistoPlotter(void *p);
   static void destruct_DTHistoPlotter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::DTHistoPlotter*)
   {
      ::DTHistoPlotter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::DTHistoPlotter));
      static ::ROOT::TGenericClassInfo 
         instance("DTHistoPlotter", "DTHistoPlotter.h", 29,
                  typeid(::DTHistoPlotter), DefineBehavior(ptr, ptr),
                  &DTHistoPlotter_Dictionary, isa_proxy, 0,
                  sizeof(::DTHistoPlotter) );
      instance.SetNew(&new_DTHistoPlotter);
      instance.SetNewArray(&newArray_DTHistoPlotter);
      instance.SetDelete(&delete_DTHistoPlotter);
      instance.SetDeleteArray(&deleteArray_DTHistoPlotter);
      instance.SetDestructor(&destruct_DTHistoPlotter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::DTHistoPlotter*)
   {
      return GenerateInitInstanceLocal((::DTHistoPlotter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::DTHistoPlotter*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *DTHistoPlotter_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::DTHistoPlotter*)0x0)->GetClass();
      DTHistoPlotter_TClassManip(theClass);
   return theClass;
   }

   static void DTHistoPlotter_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *DTCut_Dictionary();
   static void DTCut_TClassManip(TClass*);
   static void *new_DTCut(void *p = 0);
   static void *newArray_DTCut(Long_t size, void *p);
   static void delete_DTCut(void *p);
   static void deleteArray_DTCut(void *p);
   static void destruct_DTCut(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::DTCut*)
   {
      ::DTCut *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::DTCut));
      static ::ROOT::TGenericClassInfo 
         instance("DTCut", "DTCut.h", 18,
                  typeid(::DTCut), DefineBehavior(ptr, ptr),
                  &DTCut_Dictionary, isa_proxy, 0,
                  sizeof(::DTCut) );
      instance.SetNew(&new_DTCut);
      instance.SetNewArray(&newArray_DTCut);
      instance.SetDelete(&delete_DTCut);
      instance.SetDeleteArray(&deleteArray_DTCut);
      instance.SetDestructor(&destruct_DTCut);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::DTCut*)
   {
      return GenerateInitInstanceLocal((::DTCut*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::DTCut*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *DTCut_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::DTCut*)0x0)->GetClass();
      DTCut_TClassManip(theClass);
   return theClass;
   }

   static void DTCut_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *SimTreeReader_Dictionary();
   static void SimTreeReader_TClassManip(TClass*);
   static void delete_SimTreeReader(void *p);
   static void deleteArray_SimTreeReader(void *p);
   static void destruct_SimTreeReader(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SimTreeReader*)
   {
      ::SimTreeReader *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::SimTreeReader));
      static ::ROOT::TGenericClassInfo 
         instance("SimTreeReader", "SimTreeReader.h", 23,
                  typeid(::SimTreeReader), DefineBehavior(ptr, ptr),
                  &SimTreeReader_Dictionary, isa_proxy, 0,
                  sizeof(::SimTreeReader) );
      instance.SetDelete(&delete_SimTreeReader);
      instance.SetDeleteArray(&deleteArray_SimTreeReader);
      instance.SetDestructor(&destruct_SimTreeReader);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SimTreeReader*)
   {
      return GenerateInitInstanceLocal((::SimTreeReader*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::SimTreeReader*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *SimTreeReader_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::SimTreeReader*)0x0)->GetClass();
      SimTreeReader_TClassManip(theClass);
   return theClass;
   }

   static void SimTreeReader_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *FEDNtupleReader_Dictionary();
   static void FEDNtupleReader_TClassManip(TClass*);
   static void delete_FEDNtupleReader(void *p);
   static void deleteArray_FEDNtupleReader(void *p);
   static void destruct_FEDNtupleReader(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FEDNtupleReader*)
   {
      ::FEDNtupleReader *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::FEDNtupleReader));
      static ::ROOT::TGenericClassInfo 
         instance("FEDNtupleReader", "FEDNtupleReader.h", 22,
                  typeid(::FEDNtupleReader), DefineBehavior(ptr, ptr),
                  &FEDNtupleReader_Dictionary, isa_proxy, 0,
                  sizeof(::FEDNtupleReader) );
      instance.SetDelete(&delete_FEDNtupleReader);
      instance.SetDeleteArray(&deleteArray_FEDNtupleReader);
      instance.SetDestructor(&destruct_FEDNtupleReader);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FEDNtupleReader*)
   {
      return GenerateInitInstanceLocal((::FEDNtupleReader*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FEDNtupleReader*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *FEDNtupleReader_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::FEDNtupleReader*)0x0)->GetClass();
      FEDNtupleReader_TClassManip(theClass);
   return theClass;
   }

   static void FEDNtupleReader_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *FEDNumbering_Dictionary();
   static void FEDNumbering_TClassManip(TClass*);
   static void *new_FEDNumbering(void *p = 0);
   static void *newArray_FEDNumbering(Long_t size, void *p);
   static void delete_FEDNumbering(void *p);
   static void deleteArray_FEDNumbering(void *p);
   static void destruct_FEDNumbering(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FEDNumbering*)
   {
      ::FEDNumbering *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::FEDNumbering));
      static ::ROOT::TGenericClassInfo 
         instance("FEDNumbering", "FEDNumbering.h", 18,
                  typeid(::FEDNumbering), DefineBehavior(ptr, ptr),
                  &FEDNumbering_Dictionary, isa_proxy, 0,
                  sizeof(::FEDNumbering) );
      instance.SetNew(&new_FEDNumbering);
      instance.SetNewArray(&newArray_FEDNumbering);
      instance.SetDelete(&delete_FEDNumbering);
      instance.SetDeleteArray(&deleteArray_FEDNumbering);
      instance.SetDestructor(&destruct_FEDNumbering);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FEDNumbering*)
   {
      return GenerateInitInstanceLocal((::FEDNumbering*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FEDNumbering*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *FEDNumbering_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::FEDNumbering*)0x0)->GetClass();
      FEDNumbering_TClassManip(theClass);
   return theClass;
   }

   static void FEDNumbering_TClassManip(TClass* ){
   }

} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr DTHitObject::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *DTHitObject::Class_Name()
{
   return "DTHitObject";
}

//______________________________________________________________________________
const char *DTHitObject::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::DTHitObject*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int DTHitObject::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::DTHitObject*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *DTHitObject::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::DTHitObject*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *DTHitObject::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::DTHitObject*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr DTMuObject::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *DTMuObject::Class_Name()
{
   return "DTMuObject";
}

//______________________________________________________________________________
const char *DTMuObject::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::DTMuObject*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int DTMuObject::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::DTMuObject*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *DTMuObject::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::DTMuObject*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *DTMuObject::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::DTMuObject*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr DTSegmentObject::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *DTSegmentObject::Class_Name()
{
   return "DTSegmentObject";
}

//______________________________________________________________________________
const char *DTSegmentObject::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::DTSegmentObject*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int DTSegmentObject::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::DTSegmentObject*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *DTSegmentObject::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::DTSegmentObject*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *DTSegmentObject::Class()
{
   if (!fgIsA) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::DTSegmentObject*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void DTHitObject::Streamer(TBuffer &R__b)
{
   // Stream an object of class DTHitObject.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> sl;
      R__b >> layer;
      R__b >> wire;
      R__b >> X;
      R__b >> Y;
      R__b >> Z;
      R__b >> resDist;
      R__b >> resDistS1;
      R__b >> resDistS2;
      R__b >> resPos;
      R__b >> distFromWire;
      R__b >> sigmaPos;
      R__b >> angle;
      R__b >> isNoisyCell;
      R__b >> digiTime;
      R__b >> t0pulses;
      R__b.CheckByteCount(R__s, R__c, DTHitObject::IsA());
   } else {
      R__c = R__b.WriteVersion(DTHitObject::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << sl;
      R__b << layer;
      R__b << wire;
      R__b << X;
      R__b << Y;
      R__b << Z;
      R__b << resDist;
      R__b << resDistS1;
      R__b << resDistS2;
      R__b << resPos;
      R__b << distFromWire;
      R__b << sigmaPos;
      R__b << angle;
      R__b << isNoisyCell;
      R__b << digiTime;
      R__b << t0pulses;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_DTHitObject(void *p) {
      return  p ? new(p) ::DTHitObject : new ::DTHitObject;
   }
   static void *newArray_DTHitObject(Long_t nElements, void *p) {
      return p ? new(p) ::DTHitObject[nElements] : new ::DTHitObject[nElements];
   }
   // Wrapper around operator delete
   static void delete_DTHitObject(void *p) {
      delete ((::DTHitObject*)p);
   }
   static void deleteArray_DTHitObject(void *p) {
      delete [] ((::DTHitObject*)p);
   }
   static void destruct_DTHitObject(void *p) {
      typedef ::DTHitObject current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_DTHitObject(TBuffer &buf, void *obj) {
      ((::DTHitObject*)obj)->::DTHitObject::Streamer(buf);
   }
} // end of namespace ROOT for class ::DTHitObject

//______________________________________________________________________________
void DTMuObject::Streamer(TBuffer &R__b)
{
   // Stream an object of class DTMuObject.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> eta;
      R__b >> phi;
      R__b >> qpt;
      R__b >> nMuHits;
      R__b >> nStaDTHits;
      R__b >> nGlbDTHits;
      R__b >> nStaDTValidHits;
      R__b >> nGlbDTValidHits;
      R__b >> nStripHits;
      R__b >> nPixHits;
      R__b >> normChi2tk;
      R__b >> normChi2sta;
      R__b >> normChi2glb;
      R__b >> type;
      R__b >> sel;
      R__b.CheckByteCount(R__s, R__c, DTMuObject::IsA());
   } else {
      R__c = R__b.WriteVersion(DTMuObject::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << eta;
      R__b << phi;
      R__b << qpt;
      R__b << nMuHits;
      R__b << nStaDTHits;
      R__b << nGlbDTHits;
      R__b << nStaDTValidHits;
      R__b << nGlbDTValidHits;
      R__b << nStripHits;
      R__b << nPixHits;
      R__b << normChi2tk;
      R__b << normChi2sta;
      R__b << normChi2glb;
      R__b << type;
      R__b << sel;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_DTMuObject(void *p) {
      return  p ? new(p) ::DTMuObject : new ::DTMuObject;
   }
   static void *newArray_DTMuObject(Long_t nElements, void *p) {
      return p ? new(p) ::DTMuObject[nElements] : new ::DTMuObject[nElements];
   }
   // Wrapper around operator delete
   static void delete_DTMuObject(void *p) {
      delete ((::DTMuObject*)p);
   }
   static void deleteArray_DTMuObject(void *p) {
      delete [] ((::DTMuObject*)p);
   }
   static void destruct_DTMuObject(void *p) {
      typedef ::DTMuObject current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_DTMuObject(TBuffer &buf, void *obj) {
      ((::DTMuObject*)obj)->::DTMuObject::Streamer(buf);
   }
} // end of namespace ROOT for class ::DTMuObject

//______________________________________________________________________________
void DTSegmentObject::Streamer(TBuffer &R__b)
{
   // Stream an object of class DTSegmentObject.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> wheel;
      R__b >> station;
      R__b >> sector;
      R__b >> proj;
      R__b >> Xsl;
      R__b >> Ysl;
      R__b >> Zsl;
      R__b >> phi;
      R__b >> theta;
      R__b >> t0SegPhi;
      R__b >> t0SegTheta;
      R__b >> dVDriftPhi;
      R__b >> vDriftCorrPhi;
      R__b >> vDriftCorrTheta;
      R__b >> nHits;
      R__b >> nHitsPhi;
      R__b >> nHitsTheta;
      R__b >> chi2;
      tTrigMean.Streamer(R__b);
      tTrigSigma.Streamer(R__b);
      tTrigKfact.Streamer(R__b);
      hits->Streamer(R__b);
      R__b >> nAvailableHits;
      availableHits->Streamer(R__b);
      R__b >> Xglob;
      R__b >> Yglob;
      R__b >> Zglob;
      R__b.CheckByteCount(R__s, R__c, DTSegmentObject::IsA());
   } else {
      R__c = R__b.WriteVersion(DTSegmentObject::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << wheel;
      R__b << station;
      R__b << sector;
      R__b << proj;
      R__b << Xsl;
      R__b << Ysl;
      R__b << Zsl;
      R__b << phi;
      R__b << theta;
      R__b << t0SegPhi;
      R__b << t0SegTheta;
      R__b << dVDriftPhi;
      R__b << vDriftCorrPhi;
      R__b << vDriftCorrTheta;
      R__b << nHits;
      R__b << nHitsPhi;
      R__b << nHitsTheta;
      R__b << chi2;
      tTrigMean.Streamer(R__b);
      tTrigSigma.Streamer(R__b);
      tTrigKfact.Streamer(R__b);
      hits->Streamer(R__b);
      R__b << nAvailableHits;
      availableHits->Streamer(R__b);
      R__b << Xglob;
      R__b << Yglob;
      R__b << Zglob;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_DTSegmentObject(void *p) {
      return  p ? new(p) ::DTSegmentObject : new ::DTSegmentObject;
   }
   static void *newArray_DTSegmentObject(Long_t nElements, void *p) {
      return p ? new(p) ::DTSegmentObject[nElements] : new ::DTSegmentObject[nElements];
   }
   // Wrapper around operator delete
   static void delete_DTSegmentObject(void *p) {
      delete ((::DTSegmentObject*)p);
   }
   static void deleteArray_DTSegmentObject(void *p) {
      delete [] ((::DTSegmentObject*)p);
   }
   static void destruct_DTSegmentObject(void *p) {
      typedef ::DTSegmentObject current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_DTSegmentObject(TBuffer &buf, void *obj) {
      ((::DTSegmentObject*)obj)->::DTSegmentObject::Streamer(buf);
   }
} // end of namespace ROOT for class ::DTSegmentObject

namespace ROOT {
   // Wrappers around operator new
   static void *new_DTDetId(void *p) {
      return  p ? new(p) ::DTDetId : new ::DTDetId;
   }
   static void *newArray_DTDetId(Long_t nElements, void *p) {
      return p ? new(p) ::DTDetId[nElements] : new ::DTDetId[nElements];
   }
   // Wrapper around operator delete
   static void delete_DTDetId(void *p) {
      delete ((::DTDetId*)p);
   }
   static void deleteArray_DTDetId(void *p) {
      delete [] ((::DTDetId*)p);
   }
   static void destruct_DTDetId(void *p) {
      typedef ::DTDetId current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::DTDetId

namespace ROOT {
   // Wrapper around operator delete
   static void delete_HRes1DHits(void *p) {
      delete ((::HRes1DHits*)p);
   }
   static void deleteArray_HRes1DHits(void *p) {
      delete [] ((::HRes1DHits*)p);
   }
   static void destruct_HRes1DHits(void *p) {
      typedef ::HRes1DHits current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HRes1DHits

namespace ROOT {
   // Wrapper around operator delete
   static void delete_HSegment(void *p) {
      delete ((::HSegment*)p);
   }
   static void deleteArray_HSegment(void *p) {
      delete [] ((::HSegment*)p);
   }
   static void destruct_HSegment(void *p) {
      typedef ::HSegment current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HSegment

namespace ROOT {
   // Wrappers around operator new
   static void *new_DTHistoPlotter(void *p) {
      return  p ? new(p) ::DTHistoPlotter : new ::DTHistoPlotter;
   }
   static void *newArray_DTHistoPlotter(Long_t nElements, void *p) {
      return p ? new(p) ::DTHistoPlotter[nElements] : new ::DTHistoPlotter[nElements];
   }
   // Wrapper around operator delete
   static void delete_DTHistoPlotter(void *p) {
      delete ((::DTHistoPlotter*)p);
   }
   static void deleteArray_DTHistoPlotter(void *p) {
      delete [] ((::DTHistoPlotter*)p);
   }
   static void destruct_DTHistoPlotter(void *p) {
      typedef ::DTHistoPlotter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::DTHistoPlotter

namespace ROOT {
   // Wrappers around operator new
   static void *new_DTCut(void *p) {
      return  p ? new(p) ::DTCut : new ::DTCut;
   }
   static void *newArray_DTCut(Long_t nElements, void *p) {
      return p ? new(p) ::DTCut[nElements] : new ::DTCut[nElements];
   }
   // Wrapper around operator delete
   static void delete_DTCut(void *p) {
      delete ((::DTCut*)p);
   }
   static void deleteArray_DTCut(void *p) {
      delete [] ((::DTCut*)p);
   }
   static void destruct_DTCut(void *p) {
      typedef ::DTCut current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::DTCut

namespace ROOT {
   // Wrapper around operator delete
   static void delete_SimTreeReader(void *p) {
      delete ((::SimTreeReader*)p);
   }
   static void deleteArray_SimTreeReader(void *p) {
      delete [] ((::SimTreeReader*)p);
   }
   static void destruct_SimTreeReader(void *p) {
      typedef ::SimTreeReader current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::SimTreeReader

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FEDNtupleReader(void *p) {
      delete ((::FEDNtupleReader*)p);
   }
   static void deleteArray_FEDNtupleReader(void *p) {
      delete [] ((::FEDNtupleReader*)p);
   }
   static void destruct_FEDNtupleReader(void *p) {
      typedef ::FEDNtupleReader current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FEDNtupleReader

namespace ROOT {
   // Wrappers around operator new
   static void *new_FEDNumbering(void *p) {
      return  p ? new(p) ::FEDNumbering : new ::FEDNumbering;
   }
   static void *newArray_FEDNumbering(Long_t nElements, void *p) {
      return p ? new(p) ::FEDNumbering[nElements] : new ::FEDNumbering[nElements];
   }
   // Wrapper around operator delete
   static void delete_FEDNumbering(void *p) {
      delete ((::FEDNumbering*)p);
   }
   static void deleteArray_FEDNumbering(void *p) {
      delete [] ((::FEDNumbering*)p);
   }
   static void destruct_FEDNumbering(void *p) {
      typedef ::FEDNumbering current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FEDNumbering

namespace {
  void TriggerDictionaryInitialization_mydict_Impl() {
    static const char* headers[] = {
"DTCalibrationMap.h",
"DTCut.h",
"DTDetId.h",
"DTHistoPlotter.h",
"DTHitObject.h",
"DTMuObject.h",
"DTSegmentObject.h",
"FEDNtupleReader.h",
"FEDNumbering.h",
"Histograms.h",
"SimTreeReader.h",
"TTreeReader.h",
"Utils.h",
0
    };
    static const char* includePaths[] = {
"/afs/cern.ch/cms/slc6_amd64_gcc491/cms/cmssw-patch/CMSSW_7_4_2_patch1/external/slc6_amd64_gcc491/bin/../../../../../../lcg/root/6.02.00-odfocd2/include",
"/afs/cern.ch/cms/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd2/include",
"/afs/cern.ch/work/n/namapane/DT/CMSSW_7_4_2_patch1/src/DQM/DTOfflineAnalysis/test/root_lib/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$DTObjectLinkDef.h")))  DTHitObject;
class __attribute__((annotate("$clingAutoload$DTObjectLinkDef.h")))  DTMuObject;
class __attribute__((annotate("$clingAutoload$DTObjectLinkDef.h")))  DTSegmentObject;
class __attribute__((annotate("$clingAutoload$DTObjectLinkDef.h")))  DTDetId;
class __attribute__((annotate("$clingAutoload$DTObjectLinkDef.h")))  HRes1DHits;
class __attribute__((annotate("$clingAutoload$DTObjectLinkDef.h")))  HSegment;
class __attribute__((annotate("$clingAutoload$DTObjectLinkDef.h")))  DTHistoPlotter;
class __attribute__((annotate("$clingAutoload$DTObjectLinkDef.h")))  DTCut;
class __attribute__((annotate("$clingAutoload$SimTreeReader.h")))  SimTreeReader;
class __attribute__((annotate("$clingAutoload$DTObjectLinkDef.h")))  FEDNtupleReader;
class __attribute__((annotate("$clingAutoload$DTObjectLinkDef.h")))  FEDNumbering;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "DTCalibrationMap.h"
#include "DTCut.h"
#include "DTDetId.h"
#include "DTHistoPlotter.h"
#include "DTHitObject.h"
#include "DTMuObject.h"
#include "DTSegmentObject.h"
#include "FEDNtupleReader.h"
#include "FEDNumbering.h"
#include "Histograms.h"
#include "SimTreeReader.h"
#include "TTreeReader.h"
#include "Utils.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"DTCut", payloadCode, "@",
"DTDetId", payloadCode, "@",
"DTHistoPlotter", payloadCode, "@",
"DTHitObject", payloadCode, "@",
"DTMuObject", payloadCode, "@",
"DTSegmentObject", payloadCode, "@",
"FEDNtupleReader", payloadCode, "@",
"FEDNumbering", payloadCode, "@",
"HRes1DHits", payloadCode, "@",
"HSegment", payloadCode, "@",
"SimTreeReader", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("mydict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_mydict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_mydict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_mydict() {
  TriggerDictionaryInitialization_mydict_Impl();
}
