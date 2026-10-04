.DEFAULT_GOAL := run

RAINFALL_ISO ?= $(HOME)/goinfre/RainFall.iso
RAINFALL_ISO_URL ?= https://cdn.intra.42.fr/isos/RainFall.iso
RAINFALL_SSH_PORT ?= 4242
RAINFALL_ACCEL ?= tcg
RAINFALL_QEMU ?= qemu-system-i386
RAINFALL_RUNNER ?= $(shell if ! command -v qemu-system-i386 >/dev/null 2>&1 && command -v flatpak-spawn >/dev/null 2>&1; then printf 'flatpak-spawn --host'; fi)

.PHONY: run iso rainfall rainfall-iso
run: rainfall

iso: rainfall-iso

rainfall-iso:
	@$(RAINFALL_RUNNER) sh -eu -c '\
		if [ -r "$$1" ] && [ -s "$$1" ]; then exit 0; fi; \
		mkdir -p "$$(dirname "$$1")"; \
		printf "Downloading Rainfall to %s\n" "$$1"; \
		curl --fail --location --retry 3 --connect-timeout 15 --output "$$1.part" "$$2"; \
		mv "$$1.part" "$$1"' rainfall-download "$(RAINFALL_ISO)" "$(RAINFALL_ISO_URL)"

rainfall: rainfall-iso
	@printf '%s\n' 'SSH after boot: ssh -p $(RAINFALL_SSH_PORT) level0@127.0.0.1' 'Close the QEMU window to stop the VM.'
	@workdir=$$(mktemp -d) || exit 1; \
	trap 'rm -rf "$$workdir"' EXIT; \
	($(RAINFALL_RUNNER) $(RAINFALL_QEMU) -name Rainfall -machine pc,accel=$(RAINFALL_ACCEL) -m 512 \
		-cdrom "$(RAINFALL_ISO)" -boot d -display gtk \
		-nic user,model=pcnet,hostfwd=tcp:127.0.0.1:$(RAINFALL_SSH_PORT)-:4242; \
		printf '%s\n' "$$?" > "$$workdir/status") 2>&1 | tee "$$workdir/output"; \
	status=$$(cat "$$workdir/status") || exit 1; \
	if [ "$$status" -eq 0 ]; then exit 0; fi; \
	if grep -q 'Could not set up host forwarding rule' "$$workdir/output"; then \
		printf '\n%s\n' \
			'Cannot forward SSH on localhost:$(RAINFALL_SSH_PORT). The port may already be in use.' \
			'If Rainfall is already running, connect: ssh -p $(RAINFALL_SSH_PORT) level0@127.0.0.1' \
			'Otherwise close the existing VM or choose another port: make run RAINFALL_SSH_PORT=4243'; \
	else \
		printf '\nRainfall failed to start or exited with error %s. See QEMU output above.\n' "$$status"; \
	fi; \
	exit "$$status"