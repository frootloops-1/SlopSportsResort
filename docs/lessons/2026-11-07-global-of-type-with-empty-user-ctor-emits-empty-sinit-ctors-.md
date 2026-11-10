# Global of type with empty user ctor emits empty __sinit + .ctors word

- status: works
- tags: RPBox,R17
- scope: Pack/RPSports/RPBsbScene/RPBsb_8025a3e8

symptom: Global of type with empty user ctor emits empty __sinit + .ctors word
cause: Global of type with empty user ctor emits empty __sinit + .ctors word
fix: ctor-less raw type with operator T&/operator&/raw(); C cast loses hoisted .bss base
