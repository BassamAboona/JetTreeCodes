#ifndef ST_UE_JET
#define ST_UE_JET

class StUeJet : public TObject{
 public:
 StUeJet(){
    mPt = 0.;
    mEta = 999;
    mPhi = 0.;
    mE = 0.;
    mArea = -1.;
    mVecAreaPx = -1.;
    mVecAreaPy = -1.;
    mVecAreaPz = -1.;
    mVecAreaE  = -1.;
 }

  float pt() const { return mPt; }
  float eta() const { return mEta; }
  float phi() const { return mPhi; }
  float e() const { return mE; }
  float area() const { return mArea; }

  void setPt(float pt) { mPt = pt; }
  void setEta(float eta) { mEta = eta; }
  void setPhi(float phi) { mPhi = phi; }
  void setE(float e) { mE = e; }
  void setArea(float area) { mArea = area; }
  void setVecArea(float VecAreaPx, float VecAreaPy, float VecAreaPz, float VecAreaE) { mVecAreaPx = VecAreaPx; mVecAreaPy = VecAreaPy; mVecAreaPz = VecAreaPz; mVecAreaE = VecAreaE;}
//  virtual int jetId() const = 0;
//  virtual void setJetId(int id) = 0;
 private:
  float mPt;
  float mEta;
  float mPhi;
  float mE;
  float mArea;

  float mVecAreaPx;
  float mVecAreaPy;
  float mVecAreaPz;
  float mVecAreaE;

  ClassDef(StUeJet, 2);
};
#endif
