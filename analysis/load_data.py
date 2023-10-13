import pandas as pd


def load_data(sensor_data_filename: str = None) -> pd.DataFrame:
    # Read CSV file into a pandas dataframe
    if not sensor_data_filename: raise "No filename given"
    df = pd.read_csv(sensor_data_filename, parse_dates=True, header=0)

    column_names = "created_at,entry_id,period_high,period_low,ratio,temp,latitude,longitude,elevation,status".split(
        ",")
    df.columns = column_names
    df.set_index('created_at')
    return df
