/*************************************************************
 * This file was automatically generated on 2011-09-20.      *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

namespace Tinkerforge
{
	public class BrickDC : Device 
	{
		private static byte TYPE_SET_VELOCITY = 1;
		private static byte TYPE_GET_VELOCITY = 2;
		private static byte TYPE_GET_CURRENT_VELOCITY = 3;
		private static byte TYPE_SET_ACCELERATION = 4;
		private static byte TYPE_GET_ACCELERATION = 5;
		private static byte TYPE_SET_PWM_FREQUENCY = 6;
		private static byte TYPE_GET_PWM_FREQUENCY = 7;
		private static byte TYPE_FULL_BRAKE = 8;
		private static byte TYPE_GET_STACK_INPUT_VOLTAGE = 9;
		private static byte TYPE_GET_EXTERNAL_INPUT_VOLTAGE = 10;
		private static byte TYPE_GET_CURRENT_CONSUMPTION = 11;
		private static byte TYPE_ENABLE = 12;
		private static byte TYPE_DISABLE = 13;
		private static byte TYPE_IS_ENABLED = 14;
		private static byte TYPE_SET_MINIMUM_VOLTAGE = 15;
		private static byte TYPE_GET_MINIMUM_VOLTAGE = 16;
		private static byte TYPE_SET_DRIVE_MODE = 17;
		private static byte TYPE_GET_DRIVE_MODE = 18;
		private static byte TYPE_SET_CURRENT_VELOCITY_PERIOD = 19;
		private static byte TYPE_GET_CURRENT_VELOCITY_PERIOD = 20;
		private static byte TYPE_UNDER_VOLTAGE = 21;
		private static byte TYPE_EMERGENCY_SHUTDOWN = 22;
		private static byte TYPE_VELOCITY_REACHED = 23;
		private static byte TYPE_CURRENT_VELOCITY = 24;

		public delegate void UnderVoltage(ushort voltage);
		public delegate void EmergencyShutdown();
		public delegate void VelocityReached(short velocity);
		public delegate void CurrentVelocity(short velocity);

		public BrickDC(string uid) : base(uid) 
		{
			messageCallbacks[TYPE_UNDER_VOLTAGE] = new MessageCallback(CallbackUnderVoltage);
			messageCallbacks[TYPE_EMERGENCY_SHUTDOWN] = new MessageCallback(CallbackEmergencyShutdown);
			messageCallbacks[TYPE_VELOCITY_REACHED] = new MessageCallback(CallbackVelocityReached);
			messageCallbacks[TYPE_CURRENT_VELOCITY] = new MessageCallback(CallbackCurrentVelocity);
		}

		public void SetVelocity(short velocity)
		{
			byte[] data = new byte[6];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_VELOCITY, 1, data);
			LEConverter.To((ushort)6, 2, data);
			LEConverter.To(velocity, 4, data);

			ipcon.Write(this, data, TYPE_SET_VELOCITY, false);
		}

		public void GetVelocity(out short velocity)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_VELOCITY, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_VELOCITY, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetVelocity in time");
			}

			velocity = LEConverter.ShortFrom(4, answer);

			writeEvent.Set();
		}

		public void GetCurrentVelocity(out short velocity)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_CURRENT_VELOCITY, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_CURRENT_VELOCITY, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetCurrentVelocity in time");
			}

			velocity = LEConverter.ShortFrom(4, answer);

			writeEvent.Set();
		}

		public void SetAcceleration(ushort acceleration)
		{
			byte[] data = new byte[6];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_ACCELERATION, 1, data);
			LEConverter.To((ushort)6, 2, data);
			LEConverter.To(acceleration, 4, data);

			ipcon.Write(this, data, TYPE_SET_ACCELERATION, false);
		}

		public void GetAcceleration(out ushort acceleration)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_ACCELERATION, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_ACCELERATION, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetAcceleration in time");
			}

			acceleration = LEConverter.UShortFrom(4, answer);

			writeEvent.Set();
		}

		public void SetPWMFrequency(ushort frequency)
		{
			byte[] data = new byte[6];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_PWM_FREQUENCY, 1, data);
			LEConverter.To((ushort)6, 2, data);
			LEConverter.To(frequency, 4, data);

			ipcon.Write(this, data, TYPE_SET_PWM_FREQUENCY, false);
		}

		public void GetPWMFrequency(out ushort frequency)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_PWM_FREQUENCY, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_PWM_FREQUENCY, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetPWMFrequency in time");
			}

			frequency = LEConverter.UShortFrom(4, answer);

			writeEvent.Set();
		}

		public void FullBrake()
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_FULL_BRAKE, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_FULL_BRAKE, false);
		}

		public void GetStackInputVoltage(out ushort voltage)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_STACK_INPUT_VOLTAGE, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_STACK_INPUT_VOLTAGE, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetStackInputVoltage in time");
			}

			voltage = LEConverter.UShortFrom(4, answer);

			writeEvent.Set();
		}

		public void GetExternalInputVoltage(out ushort voltage)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_EXTERNAL_INPUT_VOLTAGE, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_EXTERNAL_INPUT_VOLTAGE, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetExternalInputVoltage in time");
			}

			voltage = LEConverter.UShortFrom(4, answer);

			writeEvent.Set();
		}

		public void GetCurrentConsumption(out ushort voltage)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_CURRENT_CONSUMPTION, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_CURRENT_CONSUMPTION, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetCurrentConsumption in time");
			}

			voltage = LEConverter.UShortFrom(4, answer);

			writeEvent.Set();
		}

		public void Enable()
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_ENABLE, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_ENABLE, false);
		}

		public void Disable()
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_DISABLE, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_DISABLE, false);
		}

		public void IsEnabled(out bool enabled)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_IS_ENABLED, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_IS_ENABLED, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for IsEnabled in time");
			}

			enabled = LEConverter.BoolFrom(4, answer);

			writeEvent.Set();
		}

		public void SetMinimumVoltage(ushort voltage)
		{
			byte[] data = new byte[6];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_MINIMUM_VOLTAGE, 1, data);
			LEConverter.To((ushort)6, 2, data);
			LEConverter.To(voltage, 4, data);

			ipcon.Write(this, data, TYPE_SET_MINIMUM_VOLTAGE, false);
		}

		public void GetMinimumVoltage(out ushort voltage)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_MINIMUM_VOLTAGE, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_MINIMUM_VOLTAGE, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetMinimumVoltage in time");
			}

			voltage = LEConverter.UShortFrom(4, answer);

			writeEvent.Set();
		}

		public void SetDriveMode(byte mode)
		{
			byte[] data = new byte[5];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_DRIVE_MODE, 1, data);
			LEConverter.To((ushort)5, 2, data);
			LEConverter.To(mode, 4, data);

			ipcon.Write(this, data, TYPE_SET_DRIVE_MODE, false);
		}

		public void GetDriveMode(out byte mode)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_DRIVE_MODE, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_DRIVE_MODE, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetDriveMode in time");
			}

			mode = LEConverter.ByteFrom(4, answer);

			writeEvent.Set();
		}

		public void SetCurrentVelocityPeriod(ushort period)
		{
			byte[] data = new byte[6];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_CURRENT_VELOCITY_PERIOD, 1, data);
			LEConverter.To((ushort)6, 2, data);
			LEConverter.To(period, 4, data);

			ipcon.Write(this, data, TYPE_SET_CURRENT_VELOCITY_PERIOD, false);
		}

		public void GetCurrentVelocityPeriod(out ushort period)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_CURRENT_VELOCITY_PERIOD, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_CURRENT_VELOCITY_PERIOD, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetCurrentVelocityPeriod in time");
			}

			period = LEConverter.UShortFrom(4, answer);

			writeEvent.Set();
		}

		public int CallbackUnderVoltage(byte[] data)
		{
			ushort voltage = LEConverter.UShortFrom(4, data);

			((UnderVoltage)callbacks[TYPE_UNDER_VOLTAGE])(voltage);
			return 6;
		}

		public int CallbackEmergencyShutdown(byte[] data)
		{
			((EmergencyShutdown)callbacks[TYPE_EMERGENCY_SHUTDOWN])();
			return 4;
		}

		public int CallbackVelocityReached(byte[] data)
		{
			short velocity = LEConverter.ShortFrom(4, data);

			((VelocityReached)callbacks[TYPE_VELOCITY_REACHED])(velocity);
			return 6;
		}

		public int CallbackCurrentVelocity(byte[] data)
		{
			short velocity = LEConverter.ShortFrom(4, data);

			((CurrentVelocity)callbacks[TYPE_CURRENT_VELOCITY])(velocity);
			return 6;
		}

		public void RegisterCallback(System.Delegate d)
		{
			if(d.GetType() == typeof(UnderVoltage))
			{
				callbacks[TYPE_UNDER_VOLTAGE] = d;
			}
			else if(d.GetType() == typeof(EmergencyShutdown))
			{
				callbacks[TYPE_EMERGENCY_SHUTDOWN] = d;
			}
			else if(d.GetType() == typeof(VelocityReached))
			{
				callbacks[TYPE_VELOCITY_REACHED] = d;
			}
			else if(d.GetType() == typeof(CurrentVelocity))
			{
				callbacks[TYPE_CURRENT_VELOCITY] = d;
			}
		}
	}
}
