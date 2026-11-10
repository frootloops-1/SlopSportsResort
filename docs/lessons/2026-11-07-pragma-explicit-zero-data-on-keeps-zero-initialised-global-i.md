# #pragma explicit_zero_data on keeps zero-initialised global in .sdata/.data

- status: works
- tags: RPBox,R17
- scope: Pack/RPSports/RPBsbScene/RPBsb_8025a3e8

symptom: #pragma explicit_zero_data on keeps zero-initialised global in .sdata/.data
cause: #pragma explicit_zero_data on keeps zero-initialised global in .sdata/.data
fix: solves zero-word sdata gap; __declspec(section) alone does not
