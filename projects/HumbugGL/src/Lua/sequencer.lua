-- use lua to wait for our sequencer to terminate

print("Lua Sequencer example")

-- From C++:
--        sequencer.Add( SeqEffectPtr( new SeqTimedEffect( 200, MessagePtr( new StringMessage("TwoHundret")), 5 )));
--        // one shot @ 500ms
--        MessagePtr middle( new StringMessage("Middle!"));
--        sequencer.Add( SeqEffectPtr( new SeqTimedEffect( 500, middle )));
--        // exit after 1 second, we could also use a counter in "OneHundret" and send terminate from there. Add 10ms to avoid overlap with 1
--        sequencer.Add( SeqEffectPtr( new SeqTimedEffect( 1010, MessagePtr( new Sequencer::StateMessage( Sequencer::TERMINATE)) )));
--        // this one waits for an event, send from another effect (middle)
--        sequencer.Add( SeqEffectPtr( new SeqEventEffect( middle,  MessagePtr( new StringMessage("Hey, we got a message! Creating a new one!")) )));
--        sequencer.Start();


-- and get a ref to the sequencer (we share this with the main code)
seq = pei.Sequencer()

-- register a new listerner to the sequencer
-- create a local eventlistener
listener = pei.EventListener(pei.Sequencer.StateMessage(pei.Sequencer.STOPPED))
seq:RegisterListener( listener )
-- message, efx and than add it to the sequencer
middle = pei.StringMessage("Middle!")
efx = pei.SeqTimedEffect( 500.0, middle )
seq:Add( efx )
-- or all in one line. This effect is called every 200ms and repeated 5 times. Use -1 to repeat ifinitely 
seq:Add( pei.SeqTimedEffect( 200, pei.StringMessage("TwoHundret"), 5 ))
-- This effect waits for a message and sends a new message back to the Sequencer (imagine a worked which notifies the sequencer when it's done).
seq:Add( pei.SeqEventEffect( middle, pei.StringMessage("Hey, we got a message! Bounce this back at ya'!")))
-- don't forget the terminator, else we will wait forever
seq:Add( pei.SeqTimedEffect( 1000, pei.Sequencer.StateMessage(pei.Sequencer.TERMINATE )))
-- start the sequencer
seq:Start()

-- and wait 'til it stops. The app will wait until this lua program terminates
print("Wait for Sequencer to terminate")
listener:WaitEvent()
print("All done!")
