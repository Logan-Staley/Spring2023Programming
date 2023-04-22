import pandas as pd
from sklearn.preprocessing import StandardScaler


scalar = StandardScaler()

# read in the data set
df = pd.read_csv("heart_failure_clinical_records_dataset.cvs")

# drop the 'Country' and 'City' columns
df = df.drop(['sex', 'smoking', 'platelets','diabetes', 'time','anaemia','high_blood_pressure','age'], axis=1)
dfclean = df
# save the modified data set to a new CSV file
df.to_csv("heart_failure_clinical_records_dataset_cleaned.csv", index=False)

scaled_data = scalar.fit_transform(dfclean)

scaled_data_df = pd.DataFrame(scaled_data, columns=dfclean.columns)
scaled_data_df.to_csv("heart_failure_clinical_records_dataset_scaled.csv", index=False)