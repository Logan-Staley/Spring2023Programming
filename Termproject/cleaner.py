import pandas as pd

# read in the data set
df = pd.read_csv("heart_failure_clinical_records_dataset.cvs")

# drop the 'Country' and 'City' columns
df = df.drop(['sex', 'smoking', 'platelets','diabetes','creatinine_phosphokinase', 'time', 'DEATH_EVENT','anaemia','high_blood_pressure','ejection_fraction','serum_creatinine'], axis=1)

# save the modified data set to a new CSV file
df.to_csv("heart_failure_clinical_records_dataset_cleaned_serum_sodium.csv", index=False)
